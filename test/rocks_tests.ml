(* Copyright 2016 Chetan Murthy *)

open OUnit2
open Rocks

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
	assert_raises (Assert_failure("rocks.ml",21,26))
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
	assert_raises (Failure "rocksdb_open_column_families: <IOError, None, \"/tmp/rocks_teste/aname-missing: No such file or directory\">\n")
	  (fun () -> DB.opendb "/tmp/rocks_teste/aname-missing")
      ) ;
    "open-create-missing-no-default-column-family" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	assert_raises (Failure "rocksdb_open_column_families: <InvalidArgument, None, \"Default column family not specified\">\n")
	(fun () -> DB.opendb ~opts:dboptions "/tmp/rocks_tests/aname-missing") ;
      ) ;
    "open-create-missing-ok-default-column-family" >::
      (fun ctxt ->
	let dboptions = DBOptions.create() in
	DBOptions.set_create_if_missing dboptions true ;
	let dbh = DB.opendb ~opts:dboptions
	  ~cfds:["default", CFOptions.create()]
	  "/tmp/rocks_tests/aname-missing-ok-default-column-family" in
	()
      ) ;
    "open-create-missing-ok-simple" >::
      (fun ctxt ->
	let options = Options.create() in
	Options.set_create_if_missing options true ;
	let dbh = DB0.opendb ~opts:options "/tmp/rocks_tests/aname-missing-ok-simple" in
	()
      ) ;
    "insert-get" >::
      (fun ctxt ->
	let options = Options.create() in
	Options.set_create_if_missing options true ;
	let dbh = DB0.opendb ~opts:options "/tmp/rocks_tests/aname-insert-et"  in
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
  ]
  
(* Run the tests in test suite *)
let _ = 
  if Sys.file_exists "/tmp/rocks_tests" then ignore(Unix.system "rm -rf /tmp/rocks_tests") ;
  Unix.system "mkdir -p /tmp/rocks_tests" ;
  run_test_tt_main all
;;
