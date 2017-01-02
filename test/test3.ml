open Rocks_types
open Ocaml_rocksdb
open Rocks

let main () =
let path = "../../../../tmp/myrocks-data-5.6/.rocksdb/" in
let options = DBOptions.create () in
let l = list_column_families ~opts:options path in

List.iter (fun s -> Printf.printf "%s\n" s) l ;
flush stdout ;
let cmp = Cmp.myrocks in
let cfoptions = CFOptions.create ~cmp () in
let cfds = List.map (fun n -> (n, cfoptions)) l in
let dbh = DB.opendb ~opts:options ~cfds path in

Printf.fprintf stderr "yeah, dbh\n" ;
flush stderr ;
()
;;

Printexc.catch main();;
