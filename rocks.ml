open Std
open Rocks_types
open Ocaml_rocksdb

module GCBox(T : sig
  type args
  type _t
  val create_no_gc : args -> _t
  val destroy : _t -> unit
  val name : string
end) = struct
  type t  = { it : T._t ; destroy : T._t -> unit ; gc : bool ; mutable closed : bool }
  let double_frees = ref 0
 
  let destroy t =
    if not t.closed then begin
      t.closed <- true ;
      t.destroy t.it
    end
    else if not t.gc then assert false
    else begin
      Printf.fprintf stderr "double free detected during GC finalization of %s\n" T.name;
      incr double_frees
    end

  let _raw_create ~gc x =
    { it = T.create_no_gc x ; destroy = T.destroy ; gc ; closed = false }
      
  let create ?(gc=true) x =
    let t = _raw_create ~gc x in
    if gc then Gc.finalise destroy t ;
    t
      
  let it t = t.it
end
  
module Options = struct
  module C = GCBox(struct
    let name = "options_id"
    type _t = options_id
    type args = unit
    let create_no_gc () = rocksdb_options_create()
    let destroy it = rocksdb_options_destroy it
  end)
  include C
  
  let set_create_if_missing options b =
    rocksdb_options_id_set_create_if_missing options.it b
      
  let get_create_if_missing options =
    rocksdb_options_id_get_create_if_missing options.it
end
  
module DBOptions = struct
  module C = GCBox(struct
    let name = "dboptions_id"
    type _t = dboptions_id
    type args = unit
    let create_no_gc () = rocksdb_dboptions_create()
    let destroy it = rocksdb_dboptions_destroy it
  end)
  include C

  let set_create_if_missing options b =
    rocksdb_dboptions_id_set_create_if_missing options.it b

  let get_create_if_missing options =
    rocksdb_dboptions_id_get_create_if_missing options.it
end

module Cmp = struct
  type _cmpty =
      Bytewise
    | Myrocks
  type cmpty = bool * _cmpty

  let bytewise = rocksdb_bytewise_comparator_create()
  let rev_bytewise = rocksdb_reverse_bytewise_comparator_create()
  let myrocks = rocksdb_myrocks_comparator_create()
  let rev_myrocks = rocksdb_rev_myrocks_comparator_create()

  let create = function
    | false, Bytewise -> bytewise
    | true, Bytewise -> rev_bytewise
    | false, Myrocks -> myrocks
    | true, Myrocks -> rev_myrocks
end

module CFOptions = struct
  module C = GCBox(struct
    let name = "cfoptions_id"
    type _t = cfoptions_id
    type args = unit
    let create_no_gc () = rocksdb_cfoptions_create()
    let destroy it = rocksdb_cfoptions_destroy it
  end)
  include C

  let set_comparator opts cmp =
    rocksdb_cfoptions_set_comparator opts.it cmp

  let create ?cmp ?(gc=true) () =
    let t = C.create ~gc () in
    do_option (set_comparator t) cmp ;
    t
end

module ROptions = struct
  module C = GCBox(struct
    let name = "roptions_id"
    type _t = roptions_id
    type args = unit
    let create_no_gc () = rocksdb_roptions_create()
    let destroy it = rocksdb_roptions_destroy it
  end)
  include C

  let create = C.create
end

module WOptions = struct
  module C = GCBox(struct
    let name = "woptions_id"
    type _t = woptions_id
    type args = unit
    let create_no_gc () = rocksdb_woptions_create()
    let destroy it = rocksdb_woptions_destroy it
  end)
  include C

  let create = C.create
end
  
module CFD = struct
  module C = GCBox(struct
    let name = "cfdescriptor_id"
    type _t = cfdescriptor_id
    type args = string * CFOptions.t
    let create_no_gc (name, opts) = rocksdb_cfdescriptor_create name opts.CFOptions.it
    let destroy it = rocksdb_cfdescriptor_destroy it
  end)
  include C

  let create name ?opts () =
    let options = match opts with Some o -> o | None ->
      CFOptions.create() in
    C.create (name, options)
end

let list_column_families ?opts name =
  let options = match opts with None -> DBOptions.create() | Some o -> o in
  rocksdb_list_column_families options.it name
  |> status2_to_result
  |> error_to_failure ~msg:"rocksdb_list_column_families"
  |> Array.to_list

module CFH = struct
    let destroy dbh it =
      rocksdb_cfhandle_destroy dbh it
      |> status_to_result
      |> error_to_assert_failure
end

module WriteBatch = struct
  module C = GCBox(struct
    let name = "writebatch_id"
    type _t = writebatch_id
    type args = unit
    let create_no_gc () = rocksdb_writebatch_create()
    let destroy it = rocksdb_writebatch_destroy it
  end)
  include C

  let create = C.create

  let put t key value = rocksdb_writebatch_put t.it key value
  let cf_put t cfh key value = rocksdb_writebatch_cf_put t.it cfh key value

  let delete t key = rocksdb_writebatch_delete t.it key
  let cf_delete t cfh key = rocksdb_writebatch_cf_delete t.it cfh key

  let single_delete t key = rocksdb_writebatch_single_delete t.it key
  let cf_single_delete t cfh key = rocksdb_writebatch_cf_single_delete t.it cfh key

  let delete_range t bkey ekey = rocksdb_writebatch_delete_range t.it bkey ekey
  let cf_delete_range t cfh bkey ekey = rocksdb_writebatch_cf_delete_range t.it cfh bkey ekey

end

module DB0 = struct

  let _opendb_no_gc (opts, name) =
    let options = match opts with None -> Options.create() | Some o -> o in
    rocksdb_open options.it name
    |> status2_to_result |> error_to_failure ~msg:"rocksdb_open"
    |> none_to_failure ~msg:"rocksdb_open"

  let destroy it = rocksdb_db_destroy it

  module C = GCBox(struct
    let name = "simplified db handle"
    type _t = db_id
    type args = Options.t option * string
    let create_no_gc = _opendb_no_gc
    let destroy = destroy
  end)
  include C
  let opendb ?opts ?(gc=true) name = C.create ~gc (opts, name)

  let write dbh wopts wb =
    rocksdb_write dbh.it wopts.WOptions.it wb.WriteBatch.it
    |> status_to_result |> error_to_failure ~msg:"rocksdb_write"

  let get dbh ropts key =
    rocksdb_get dbh.it ropts.ROptions.it key
    |> status2_to_result |> error_to_failure ~msg:"rocksdb_get"
end

module DB = struct
  type dbh = {
    dbh : db_id ;
    cfhs : cfhandle_id list ;
  }

  let _opendb_no_gc (opts, cfds, name) =
    let options = match opts with None -> DBOptions.create() | Some o -> o in
    let cfds =
      match cfds with Some a -> a
      | None -> begin
	try
	  list_column_families ~opts:options name
	with Failure _ -> []
      end
      |>  List.map (fun n -> CFD.create n ()) in
    let cfds = Array.of_list (List.map CFD.it cfds) in
    rocksdb_open_column_families options.it name cfds
    |> status3_to_result |> error_to_failure ~msg:"rocksdb_open_column_families"
    |> (function cfds, None -> failwith "rocksdb_open_column_families: OK status, but no dbh!"
      | (cfhs, Some dbh) -> {cfhs = Array.to_list cfhs ; dbh})

  let destroy it =
    let destroy1 cfh =
      CFH.destroy it.dbh cfh in
    List.iter destroy1 it.cfhs ;
    rocksdb_db_destroy it.dbh

  module C = GCBox(struct
    let name = "full db handle"
    type _t = dbh
    type args = DBOptions.t option * CFD.t list option * string
    let create_no_gc = _opendb_no_gc
    let destroy = destroy
  end)
  include C
  let opendb ?opts ?cfds ?(gc=true) name = C.create ~gc (opts, cfds, name)

  let write dbh wopts wb =
    rocksdb_write dbh.it.dbh wopts.WOptions.it wb.WriteBatch.it
    |> status_to_result |> error_to_failure ~msg:"rocksdb_write"

  let get dbh ropts key =
    rocksdb_get dbh.it.dbh ropts.ROptions.it key
    |> status2_to_result |> error_to_failure ~msg:"rocksdb_get"

  let cf_get dbh ropts cfh key =
    rocksdb_cf_get dbh.it.dbh ropts.ROptions.it cfh key
    |> status2_to_result |> error_to_failure ~msg:"rocksdb_get"
end
