#!/usr/bin/perl

print <<"EOF";
version = "2016-12-27"
requires = "result,threads,core_kernel"
description = "Rocksdb wrapper library (using camlidl)"
archive(byte) = "ocaml_rocksdb.cma"
archive(native) = "ocaml_rocksdb.cmxa"
linkopts = "-cclib -L$ENV{'ROCKS_LIBDIR'} -cclib -l$ENV{'ROCKS_LIB'}"
EOF

