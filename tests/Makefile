# Makefile,v
# Copyright (c) INRIA 2007-2017

WD=$(shell pwd)
TOP=..
include $(TOP)/config/Makefile.sub

DESTDIR=

PACKAGES := $(PACKAGES),ocaml_rocksdb,oUnit

ALLSRC=$(shell ls *.ml)
ALLPACKAGES=$(PACKAGES)

OCAMLCFLAGS := $(OCAMLCFLAGS) -thread

TESTS= \
	rocks_tests.byte \

ML=\
	rocks_tests.ml

all: $(TESTS) $(TESTS:.byte=.opt)

test: $(TESTS:.byte=)

% : %.opt
	mkdir -p _build && ./$<

rocks_tests.byte: rocks_tests.cmo
	$(LAUNCH) $(OCAMLFIND) ocamlc $(DEBUG) $(WARNERR) -package $(PACKAGES) \
	-linkpkg -custom -thread $^ -o $@

rocks_tests.opt: rocks_tests.cmx
	$(LAUNCH) $(OCAMLFIND) ocamlopt $(DEBUG) $(WARNERR) -package $(PACKAGES) \
	-linkpkg -thread $^ -o $@

clean::
	rm -f  *.ppo.*
