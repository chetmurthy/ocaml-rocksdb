#include "version.inc"

let top = try Sys.getenv "TOP" with Not_found -> "" ;;
let destdir = ref (top ^ "/local-install") ;;

Arg.(parse [
         "-destdir", (Arg.String (fun s -> destdir := s)),
         ("<path>    Set the destination directory (default: " ^
	    !destdir ^ ")")
       ]
       (fun _ -> failwith "mk_meta: no anonymous args supported")
     "mk_meta -destdir <dir>")
;;

Fmt.(pf stdout {|# Specifications for the "ocaml_rocksdb" package:
version = "%s"
description = "OCaml RocksDB interface"

requires(toploop) = "result,threads,core"
archive(toploop) = "ocaml_rocksdb.cma"

requires = "result,threads,core"
archive(byte) = "ocaml_rocksdb.cma"
archive(native) = "ocaml_rocksdb.cmxa"
|} version)
