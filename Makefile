# Makefile,v
# Copyright (c) INRIA 2007-2017

ifdef BACKLEVEL_ROCKSDB
export PKG_CONFIG_PATH=$(shell pwd)/backlevel-rocksdb-pkgconfig:
$(info PKG_CONFIG_PATH is $(shell pwd)/backlevel-rocksdb-pkgconfig: )
endif
#export PKG_CONFIG_PATH=$(HOME)/Hack/Rocksdb/v5.17.2-shared/lib/pkgconfig/
#export PKG_CONFIG_PATH=$(HOME)/Hack/Rocksdb/v6.11.4-shared/lib/pkgconfig/
#export PKG_CONFIG_PATH=$(HOME)/Hack/Rocksdb/v7.8.3-shared/lib/pkgconfig/
#export PKG_CONFIG_PATH=$(HOME)/Hack/Rocksdb/v8.9.1-shared/lib/pkgconfig/
#export PKG_CONFIG_PATH=$(HOME)/Hack/Rocksdb/v9.8.4-shared/lib/pkgconfig/
#export PKG_CONFIG_PATH=$(HOME)/Hack/Rocksdb/v9.8.4-static/lib/pkgconfig/

TOP=.
include $(TOP)/config/Makefile.top

WD=$(shell pwd)
DESTDIR=

SYSDIRS= lib

TESTDIRS= tests

all: sys
	set -e; for i in $(TESTDIRS); do cd $$i; $(MAKE) all; cd ..; done

test: all
	set -e; for i in $(TESTDIRS); do cd $$i; $(MAKE) test; cd ..; done

sys: plugins

plugins:
	set -e; for i in $(SYSDIRS); do cd $$i; $(MAKE) all; cd ..; done

doc: all
	set -e; for i in $(SYSDIRS); do cd $$i; $(MAKE) doc; cd ..; done
	rm -rf docs
	tools/make-docs ocaml-rocksdb docs
	make -C doc html

install: sys
	$(OCAMLFIND) remove ocaml_rocksdb || true
	$(OCAMLFIND) install ocaml_rocksdb local-install/lib/ocaml_rocksdb/*

uninstall:
	$(OCAMLFIND) remove ocaml_rocksdb || true

clean::
	set -e; for i in $(SYSDIRS) $(TESTDIRS); do cd $$i; $(MAKE) clean; cd ..; done
	rm -rf docs local-install

depend:
	set -e; for i in $(SYSDIRS) $(TESTDIRS); do cd $$i; $(MAKE) depend; cd ..; done
