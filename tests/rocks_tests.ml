(* Copyright 2016 Chetan Murthy *)

open OUnit2
open Ocaml_rocksdb.Rocks

let raises f =
  try
    let _ = f () in None
  with e ->
    Some e

let assert_raises_exn_pred ?msg ?exnmsg exnpred (f: unit -> 'a) =
  let pexn =
    Printexc.to_string
  in
  let get_error_string () =
    let str =
      Format.sprintf
        "expected exception %s, but no exception was raised."
        (match exnmsg with None -> "<no message provided>" | Some msg -> msg)
    in
      match msg with
          None ->
            assert_failure str

        | Some s ->
            assert_failure (s^"\n"^str)
  in
    match raises f with
       None ->
          assert_failure (get_error_string ())

      | Some e ->
          let msg = match msg with None -> "" | Some s -> s in
          assert_bool msg (exnpred e)

let matches ~pattern text =
  match Str.search_forward (Str.regexp pattern) text 0 with
    _ -> true
  | exception Not_found -> false


let assert_raises_exn_pattern pattern f =
  assert_raises_exn_pred
    (function
           Failure msg when matches ~pattern msg -> true
         | _ -> false
    )
    f

let canon l = List.sort Stdlib.compare l

let all = "all_tests" >:::
  [
    "single-free" >::
      (fun ctxt ->
	let opts = DBOptions.create() in
	DBOptions.destroy opts ;
      ) ;
    "double-free" >::
      (fun ctxt ->
	let opts = DBOptions.create ~gc:false () in
	DBOptions.destroy opts ;
	assert_raises (Assert_failure("rocks.ml",31,26))
	(fun () -> DBOptions.destroy opts) ;
      ) ;
    "double-free-gc" >::
      (fun ctxt ->
	let opts = DBOptions.create() in
	DBOptions.destroy opts ;
	let n_double_frees0 = !DBOptions.double_frees in
	DBOptions.destroy opts ;
	let n_double_frees1 = !DBOptions.double_frees in
	assert_equal n_double_frees1 (1 + n_double_frees0) ;
      ) ;
    "list-0" >::
      (fun ctxt ->
	assert_raises_exn_pattern "IOError.*_build/CURRENT"
	  (fun () -> list_column_families "_build") ;
      ) ;
    "dboptions-attr" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	assert_bool "better be false" (not (DBOptions.get_create_if_missing dboptions)) ;
	assert_bool "better be false (2)" (not (DBOptions.export dboptions).create_if_missing) ;
	DBOptions.set_create_if_missing dboptions true ;
	assert_bool "better be true" (DBOptions.get_create_if_missing dboptions) ;
	assert_bool "better be true (2)" (DBOptions.export dboptions).create_if_missing ;
      ) ;
    "open-create-missing-fails" >::
      (fun ctxt ->
	assert_raises_exn_pattern "IOError.*No such file or directory"
	  (fun () -> DB.opendb "_build/rocks_teste/aname-missing")
      ) ;
    "open-create-missing-no-default-column-family" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	assert_raises (Failure "rocksdb_open_column_families: <InvalidArgument, None, Invalid argument: Default column family not specified>\n")
	(fun () -> DB.opendb ~opts:dboptions "_build/rocks_tests/aname-missing") ;
      ) ;
    "open-create-missing-ok-default-column-family" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let dbh = DB.opendb ~opts:dboptions
	  ~cfds:["default", CFOptions.create()]
	  "_build/rocks_tests/aname-missing-ok-default-column-family" in
	()
      ) ;
    "open-create-missing-ok-simple" >::
      (fun ctxt ->
	let options = Options.create() in
	Options.set_create_if_missing options true ;
	let dbh = DB0.opendb ~opts:options "_build/rocks_tests/aname-missing-ok-simple" in
	()
      ) ;
    "insert-get-0" >::
      (fun ctxt ->
	let options = Options.create() in
	Options.set_create_if_missing options true ;
	let dbh = DB0.opendb ~opts:options "_build/rocks_tests/aname-insert-get-0"  in
	assert_raises Not_found
	  (fun () -> DB0.get dbh "foo") ;
	DB0.delete dbh "foo" ;
	DB0.put dbh "foo" "bar" ;
	assert_equal "bar" (DB0.get dbh "foo") ;
	DB0.delete dbh "foo" ;
	assert_raises Not_found
	  (fun () -> DB0.get dbh "foo") ;
	()
      ) ;
    "insert-get-1" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	let cfoptions = CFOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let cfname = "default" in
	let dbh = DB.opendb ~opts:dboptions
	  ~cfds:[cfname,cfoptions]
	  "_build/rocks_tests/aname-insert-get-1"  in
	assert_raises Not_found
	  (fun () -> DB.cf_get dbh ~cfname "foo") ;
	DB.cf_delete dbh ~cfname "foo" ;
	DB.cf_put dbh ~cfname "foo" "bar" ;
	assert_equal "bar" (DB.cf_get dbh ~cfname "foo") ;
	DB.cf_delete dbh ~cfname "foo" ;
	assert_raises Not_found
	  (fun () -> DB.cf_get dbh ~cfname "foo") ;
	()
      ) ;
    "cf-0" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	let cfoptions = CFOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let cfname0 = "default" in
	let cfname1 = "cf1" in
	assert_raises_exn_pattern "InvalidArgument.*cf1"
	(fun () -> DB.opendb ~opts:dboptions
	  ~cfds:[cfname0, cfoptions; cfname1, cfoptions]
	  "_build/rocks_tests/aname-cf-0") ;
	()
      ) ;
    "cf-1" >::
      (fun ctxt ->
	let path = "_build/rocks_tests/aname-cf-1" in
	let dboptions = DBOptions.create() in
	let cfoptions = CFOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let cfname0 = "default" in
	let cfname1 = "cf1" in
	DB.with_db ~opts:dboptions ~cfds:[cfname0, cfoptions] path
	  ~f:(fun dbh ->
	    assert_equal [cfname0] (list_column_families path) ;
	    DB.create_cf dbh ~opts:cfoptions cfname1 ;
	    assert_equal (canon [cfname0; cfname1]) (canon (list_column_families path)) ;
	    let cfname = cfname1 in
	    begin
	      assert_raises Not_found
		(fun () -> DB.cf_get dbh ~cfname "foo") ;
	      DB.cf_delete dbh ~cfname "foo" ;
	      DB.cf_put dbh ~cfname "foo" "bar" ;
	      assert_equal "bar" (DB.cf_get dbh ~cfname "foo") ;
	      DB.cf_delete dbh ~cfname "foo" ;
	      assert_raises Not_found
		(fun () -> DB.cf_get dbh ~cfname "foo") ;
	    end) ;
	DB.with_db ~opts:dboptions ~cfds:[cfname0, cfoptions; cfname1, cfoptions] path
	  ~f:(fun dbh ->
	    let cfname = cfname1 in
	    begin
	      assert_raises Not_found
		(fun () -> DB.cf_get dbh ~cfname "foo") ;
	      DB.cf_delete dbh ~cfname "foo" ;
	      DB.cf_put dbh ~cfname "foo" "bar" ;
	      assert_equal "bar" (DB.cf_get dbh ~cfname "foo") ;
	      DB.cf_delete dbh ~cfname "foo" ;
	      assert_raises Not_found
		(fun () -> DB.cf_get dbh ~cfname "foo") ;
	    end ;
	    DB.drop_cf dbh cfname1 ;
	    assert_equal [cfname0] (list_column_families path)
	  );
	()
      ) ;
    "iterator-0" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	let cfoptions = CFOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let cfname = "default" in
	let dbh = DB.opendb ~opts:dboptions
	  ~cfds:[cfname,cfoptions]
	  "_build/rocks_tests/aname-iterator-0"  in
	DB.with_iterator dbh ~f:(fun it ->
	  assert_bool "better NOT be valid" (not (Iterator.valid it)) ;
	  Iterator.seek_to_first it ;
	  assert_bool "better NOT be valid (2)" (not (Iterator.valid it))
	);
	()
      ) ;
    "iterator-1" >::
      (fun ctxt ->
	let path = "_build/rocks_tests/aname-iterator-1" in
	let dboptions = DBOptions.create() in
	let cfoptions = CFOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let cfname0 = "default" in
	let cfname1 = "cf1" in
	DB.with_db ~opts:dboptions ~cfds:[cfname0,cfoptions] path
       ~f:(fun dbh ->
	 DB.create_cf dbh ~opts:cfoptions cfname1 ;
	 List.iter (fun s ->
	   DB.put dbh s s ;
	   DB.cf_put ~cfname:cfname1 dbh s s ;
	 )
	  ["a"; "aa"; "ab";
	   "c"; "ca"; "cb";
	   "e"] ;
	 ()
       ) ;

	let iter_test it =
	  assert_bool "better NOT be valid" (not (Iterator.valid it)) ;
	  Iterator.seek_to_first it ;
	  assert_bool "better BE valid" (Iterator.valid it) ;
	  assert_equal "a" (Iterator.key it) ;
	  assert_equal "a" (Iterator.value it) ;
	  Iterator.seek_for_prev it "b" ;
	  assert_equal "ab" (Iterator.key it) ;
	  Iterator.seek_for_prev it "c" ;
	  assert_equal "c" (Iterator.key it) ;
	  Iterator.seek_to_last it ;
	  Iterator.next it ;
	  assert_bool "better NOT be valid (2)" (not (Iterator.valid it)) ;
	  let l = (List.map fst (Iterator.to_list (Iterator.forward ~from:"a" ~ok:(fun k v -> k <= "ab") it))) in
	  assert_equal ~msg:"forward-1" ["a"; "aa"; "ab"]
	    (List.map fst (Iterator.to_list (Iterator.forward ~from:"a" ~ok:(fun k v -> k <= "ab") it))) ;
	  assert_equal ~msg:"reverse-1" ["ab"; "aa"; "a"]
	    (List.map fst (Iterator.to_list (Iterator.reverse ~from:"ab" ~ok:(fun k v -> k >= "a") it)))
	in

	DB.with_db ~opts:dboptions ~cfds:[cfname0,cfoptions; cfname1,cfoptions] path
	  ~f:(fun dbh ->
	    DB.with_iterator dbh ~f:iter_test ;
	    DB.with_iterator dbh ~cfname:cfname1 ~f:iter_test ;
	    ()
	  ) ;

	DB.with_db ~readonly:true ~opts:dboptions ~cfds:[cfname0,cfoptions; cfname1,cfoptions] path
	  ~f:(fun dbh ->
	    DB.with_iterator dbh ~f:iter_test ;
	    DB.with_iterator dbh ~cfname:cfname1 ~f:iter_test ;
	    ()
	  ) ;
      ) ;
  ]
  
(* Run the tests in test suite *)
let _ = 
  if Sys.file_exists "_build/rocks_tests" then ignore(Unix.system "rm -rf _build/rocks_tests") ;
  Unix.system "mkdir -p _build/rocks_tests" ;
  run_test_tt_main all
;;
