# Makefile,v
# Copyright (c) INRIA 2007-2017

WD=$(shell pwd)
TOP=..
include $(TOP)/config/Makefile.sub

DESTDIR=

PACKAGES := $(PACKAGES),ocaml_rocksdb,oUnit,str

ALLSRC=$(shell ls *.ml)
ALLPACKAGES=$(PACKAGES)

OCAMLCFLAGS := $(OCAMLCFLAGS) -thread

TESTS= \
	rocks_tests.byte.TEST \
	rocks_tests.noncustom.byte.TEST \
	rocks_tests.opt.TEST \

ML=\
	rocks_tests.ml

all: $(TESTS:.TEST=)

test: $(TESTS)

%.TEST : %
	mkdir -p _build && ./$<

rocks_tests.byte: rocks_tests.cmo
	$(LAUNCH) $(OCAMLFIND) ocamlc $(DEBUG) $(WARNERR) -package $(PACKAGES) \
	-linkpkg -custom -thread $^ -o $@

rocks_tests.noncustom.byte: rocks_tests.cmo
	$(LAUNCH) $(OCAMLFIND) ocamlc $(DEBUG) $(WARNERR) -package $(PACKAGES) \
	-dllpath $(TOP)/local-install/lib/ocaml_rocksdb \
	-linkpkg -thread $^ -o $@

rocks_tests.opt: rocks_tests.cmx
	$(LAUNCH) $(OCAMLFIND) ocamlopt $(DEBUG) $(WARNERR) -package $(PACKAGES) \
	-linkpkg -thread $^ -o $@

clean::
	rm -rf  *.ppo.* _build
