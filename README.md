# Ocaml RocksDB interface

This is an OCaml RocksDB foreign-function interface, generated using
[cppffigen][cppffigen].  There is another, [orocksdb][orocksdb] which
I used extensively before writing this, and I'm certainly not trying
to compete with that library.  Indeed, unless you need function
specific to this library, I would recommend you use that one instead.

The salient difference between this library and orocksdb (aside from
the immaturity of this one) is that this library is based on
wrappering the RocksDB C++ interface directly, rather than wrappering
the RocksDB C API.  In my opinion, wrappering the C++ API is much,
much, much simpler, so it is easy to extend the wrappering to all
parts of the RocksDB C++ API that one wishes to expose in Ocaml.

The strongest reason for releasing this library, is simply as an
example of cppffigen in action.

## Installation

Once you've installed `cppffigen` and rocksdb, to install this library
is straightforward: edit the Makefile and modify

```
ROCKS_LIB=rocksdb
ROCKS_INSTALL=/home/chet/Hack/IL-DEV/rocksdb-myrocks
ROCKS_LIBDIR=/home/chet/Hack/IL-DEV/rocksdb-myrocks/lib
ROCKS_VERSION=myrocks
```

to match your rocksdb installation.  Then

```
make all install
```

In the `test` subdirectory is a test suite to exercise the generated
interface.  This test-suite is built using oasis and oUnit.  To build
and run the testsuite:

```
cd tests
oasis setup
ocaml setup.ml -configure --enable-tests
make test
```

#### License

This code is released under an [Apache 2.0 license][/LICENSE]

[cppffigen]: https://github.com/chetmurthy/ocaml-cppffigen
[orocksdb]: https://github.com/domsj/orocksdb
[/LICENSE]: /LICENSE
