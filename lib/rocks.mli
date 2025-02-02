module type GCABLE = sig
  type t
  val double_frees : int ref
  val destroy : t -> unit
end

module Options : sig
  include GCABLE
  val create : ?gc:bool -> unit -> t
  val default : t
  val unopt : t option -> t
  val set_create_if_missing : t -> bool -> unit
  val get_create_if_missing : t -> bool
end

module DBOptions : sig
  include GCABLE
  val create : ?gc:bool -> unit -> t
  val default : t
  val unopt : t option -> t
  val set_create_if_missing : t -> bool -> unit
  val get_create_if_missing : t -> bool
  val export : t -> Ffi.DBOptionsST.t
end

module Cmp : sig
  type _cmpty = Bytewise | Myrocks
  type cmpty = bool * _cmpty
  val bytewise : Ffi.Types.comparator_id
  val rev_bytewise : Ffi.Types.comparator_id
  val myrocks : Ffi.Types.comparator_id
  val rev_myrocks : Ffi.Types.comparator_id
  val create : bool * _cmpty -> Ffi.Types.comparator_id
end

module CFOptions : sig
  include GCABLE
  val default : t
  val unopt : t option -> t
  val set_comparator : t -> Ffi.Types.comparator_id -> unit
  val create : ?cmp:Ffi.Types.comparator_id -> ?gc:bool -> unit -> t
end

module ROptions : sig
  include GCABLE
  val create : ?gc:bool -> unit -> t
  val default : t
  val unopt : t option -> t
end

module WOptions : sig
  include GCABLE
  val create : ?gc:bool -> unit -> t
  val default : t
  val unopt : t option -> t
end

val list_column_families : ?opts:DBOptions.t -> string -> string list

module CFH : sig
  type t
  val destroy : Ffi.Types.db_id -> t -> unit
end

module WriteBatch : sig
  include GCABLE
  val create : ?gc:bool -> unit -> t

  val put : t -> string -> string -> unit
  val cf_put : t -> CFH.t -> string -> string -> unit

  val delete : t -> string -> unit
  val cf_delete : t -> CFH.t -> string -> unit

  val single_delete : t -> string -> unit
  val cf_single_delete : t -> CFH.t -> string -> unit

  val delete_range : t -> string -> string -> unit
  val cf_delete_range : t -> CFH.t -> string -> string -> unit
end

module Iterator : sig
  include GCABLE
  val create : ?gc:bool -> Ffi.Types.db_id * ROptions.t option * CFH.t option -> t
  val valid : t -> bool
  val seek_to_first : t -> unit
  val seek_to_last : t -> unit
  val seek : t -> string -> unit
  val seek_for_prev : t -> string -> unit
  val next : t -> unit
  val prev : t -> unit
  val key : t -> string
  val value : t -> string
  val status : t -> (unit, string) Result.result
  val forward : ?from:string -> ?ok:(string -> string -> bool) -> t -> f:(string -> string -> 'a) -> unit
  val reverse : ?from:string -> ?ok:(string -> string -> bool) -> t -> f:(string -> string -> 'a) -> unit
  val to_list : (f:(string -> string -> unit) -> unit) -> (string * string) list
end

module DB0 : sig
  include GCABLE
  val opendb : ?readonly:bool ->
    ?error_if_log_file_exist:bool ->
    ?opts:Options.t -> ?gc:bool -> string -> t
  val with_db : ?readonly:bool ->
    ?error_if_log_file_exist:bool ->
    ?opts:Options.t -> string -> f:(t -> 'a) -> 'a
  val write : t -> ?wopts:WOptions.t -> WriteBatch.t -> unit
  val get : t -> ?ropts:ROptions.t -> string -> string
  val put : t -> ?wopts:WOptions.t -> string -> string -> unit
  val delete : t -> ?wopts:WOptions.t -> string -> unit
  val iterator : ?gc:bool -> ?opts:ROptions.t -> t -> Iterator.t
  val with_iterator : ?opts:ROptions.t -> t -> f:(Iterator.t -> 'a) -> 'a
end

module DB : sig
  include GCABLE
  val opendb : ?readonly:bool ->
           ?error_if_log_file_exist:bool ->
           ?opts:DBOptions.t -> ?cfopts:CFOptions.t ->
           ?cfds:(string * CFOptions.t) list -> ?gc:bool -> string -> t
  val with_db : ?readonly:bool ->
           ?error_if_log_file_exist:bool ->
           ?opts:DBOptions.t -> ?cfopts:CFOptions.t ->
           ?cfds:(string * CFOptions.t) list -> string -> f:(t -> 'a) -> 'a
  val cfh : t -> string -> CFH.t
  val create_cf : t -> ?opts:CFOptions.t -> string -> unit
  val drop_cf : t -> string -> unit
  val write : t -> ?wopts:WOptions.t -> WriteBatch.t -> unit

  val get : t -> ?ropts:ROptions.t -> string -> string
  val cf_get : t -> ?ropts:ROptions.t -> cfname:string -> string -> string

  val put : t -> ?wopts:WOptions.t -> string -> string -> unit
  val cf_put : t -> ?wopts:WOptions.t -> cfname:string -> string -> string -> unit

  val delete : t -> ?wopts:WOptions.t -> string -> unit
  val cf_delete : t -> ?wopts:WOptions.t -> cfname:string -> string -> unit

  val iterator : ?gc:bool -> ?opts:ROptions.t -> ?cfname:string -> t -> Iterator.t
  val with_iterator : ?opts:ROptions.t -> ?cfname:string -> t -> f:(Iterator.t -> 'a) -> 'a
end
