# Makefile,v
# Copyright (c) INRIA 2007-2017

WD=$(shell pwd)
TOP=..
include $(TOP)/config/Makefile.sub

DESTDIR=

TARGET_PACKAGE := ocaml_rocksdb
TARGET := $(TARGET_PACKAGE).cma
ML = misc.ml rocks_types.ml ffi.ml rocks.ml
MLI = rocks_types.mli ffi.mli rocks.mli

ALLSRC = $(ML) $(MLI)
ALLPACKAGES = $(PACKAGES)

CPPFFIGEN=$(OCAMLFIND) cppffigen/cppffigen
OCAMLCFLAGS := $(OCAMLCFLAGS) -for-pack Ocaml_rocksdb -linkall -thread

all: $(TARGET) $(TARGET:.cma=.cmxa)
	OCAMLFIND_LDCONF=ignore $(MAKE) DESTDIR=$(WD)/$(TOP)/local-install/ install

doc: $(CMT) $(CMTI)

TARGET_INSTALL_FILES= $(PACKED_ARCHIVE_TARGET_INSTALL_FILES)  dll$(TARGET_PACKAGE).so lib$(TARGET_PACKAGE).a
install:: META $(TARGET_INSTALL_FILES) $(DEFAULT_INSTALL_FILES)
	touch META
	mkdir -p $(DESTDIR)/lib
	$(OCAMLFIND) remove $(TARGET_PACKAGE) -destdir $(DESTDIR)/lib
	$(OCAMLFIND) install $(TARGET_PACKAGE) -destdir $(DESTDIR)/lib META $(DEFAULT_INSTALL_FILES) $(TARGET_INSTALL_FILES)

clean::
	$(OCAMLFIND) remove $(TARGET_PACKAGE) -destdir $(WD)/$(TOP)/local-install/lib
	rm -rf META dll$(TARGET_PACKAGE).so lib$(TARGET_PACKAGE).a ffi.ml* ffi_stubs.cc

$(TARGET_PACKAGE).cmo $(TARGET_PACKAGE).cmi: $(CMO)
	$(OCAMLFIND) ocamlc $(DEBUG) -pack -o $(TARGET_PACKAGE).cmo $^

$(TARGET_PACKAGE).cmx: $(CMO:.cmo=.cmx)
	$(OCAMLFIND) ocamlopt $(DEBUG) -pack -o $(TARGET_PACKAGE).cmx $^

$(TARGET_PACKAGE).cma $(TARGET_PACKAGE).cmxa dll$(TARGET_PACKAGE).so lib$(TARGET_PACKAGE).a: $(TARGET_PACKAGE).cmo $(TARGET_PACKAGE).cmx  ffi_stubs.o
	ocamlmklib -verbose -o $(TARGET_PACKAGE) $(TARGET_PACKAGE).cmo $(TARGET_PACKAGE).cmx ffi_stubs.o $(OCAMLMKLIB_FLAGS)

ffi.ml ffi.mli ffi_stubs.cc: rocksdb-ffi.idl
	$(CPPFFIGEN) --output ml < rocksdb-ffi.idl > ffi.ml
	$(CPPFFIGEN) --output mli < rocksdb-ffi.idl > ffi.mli
	$(CPPFFIGEN) --output cpp < rocksdb-ffi.idl > ffi_stubs.cc

OCAMLLIB := $(shell ocamlc -where)
ROCKSDB_CFLAGS = $(shell pkg-config --cflags rocksdb)
ROCKSDB_LDFLAGS = \
  $(shell pkg-config --libs rocksdb) \
  $(shell pkg-config --libs snappy) \
  $(shell pkg-config --libs libzstd) \
  $(shell pkg-config --libs zlib) \
  $(shell pkg-config --libs liblz4) \
  -lbz2

ROCKSDB_LDFLAGS:= \
  -Wl,-rpath=$(shell pkg-config --variable=libdir rocksdb) \
  $(ROCKSDB_LDFLAGS)

CPPFFIGEN_INCLUDES = $(shell ocamlfind query cppffigen)
CXXFLAGS += -g2 -I. -I$(CPPFFIGEN_INCLUDES) -I$(OCAMLLIB) -std=c++17 -fno-rtti $(ROCKSDB_CFLAGS)
OCAMLMKLIB_FLAGS= $(ROCKSDB_LDFLAGS) -lstdc++

ffi_stubs.o: ffi_stubs.cc
	g++ -c -fPIC ${CXXFLAGS} -DPIC -o ffi_stubs.o ffi_stubs.cc
