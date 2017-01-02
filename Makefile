ROCKS_LIB=rocksdb
ROCKS_INSTALL=/home/chet/Hack/IL-DEV/rocksdb-myrocks
ROCKS_LIBDIR=/home/chet/Hack/IL-DEV/rocksdb-myrocks/lib
ROCKS_VERSION=myrocks

#ROCKS_VERSION ?= 4.11.2
#ROCKS_INSTALL ?= /usr/local
#ROCKS_LIBDIR ?= $(ROCKS_INSTALL)/lib
#ROCKS_LIB ?= rocksdb
export ROCKS_LIB ROCKS_LIBDIR ROCKS_INSTALL

ifeq ($(ROCKS_VERSION),myrocks)
  UNIFDEF_ARGS = -D ROCKS_VERSION_MYROCKS
else
  UNIFDEF_ARGS = -U ROCKS_VERSION_MYROCKS
endif

OCAMLLIB := $(shell ocamlc -where)
OCAMLMKLIB_FLAGS= \
  -Wl,-rpath=$(ROCKS_LIBDIR) -L$(ROCKS_LIBDIR) -l$(ROCKS_LIB) \
  -lstdc++

RESULT=ocaml_rocksdb
RESULT_PACKAGE=ocaml-rocksdb

CXXFLAGS += -g -I. -I`ocamlfind query cppffigen` -I$(OCAMLLIB) -I$(ROCKS_INSTALL)/include -std=gnu++11

PACKS = utils,threads

ML= rocks_types.ml $(RESULT).ml rocks.ml
CMO= $(patsubst %.ml,%.cmo, $(ML))
CMX= $(patsubst %.ml,%.cmx, $(ML))
CMI= $(patsubst %.ml,%.cmi, $(ML))
OBJECTS = $(CMO) $(CMX) $(CMI)

all: $(RESULT).cma $(RESULT).cmxa dll$(RESULT).so

$(RESULT).cma $(RESULT).cmxa dll$(RESULT).so: $(OBJECTS) $(RESULT)_stubs.o
	    ocamlmklib -verbose -o $(RESULT) $(CMO) $(CMX) $(RESULT)_stubs.o $(OCAMLMKLIB_FLAGS)

$(CMO) $(CMI): $(ML)
	ocamlfind ocamlc -thread -package $(PACKS) -c -g $(ML)

$(CMX): $(ML) $(CMI)
	ocamlfind ocamlopt -thread -package $(PACKS) -c $(ML)

$(RESULT).ml $(RESULT)_stubs.cc: rocksdb-ffi.idl
	cppffigen --output ml < rocksdb-ffi.idl > $(RESULT).ml
	cppffigen --output cpp < rocksdb-ffi.idl > $(RESULT)_stubs.cc

$(RESULT)_stubs.o: $(RESULT)_stubs.cc
	g++ -c -fPIC ${CXXFLAGS} -DPIC -o $(RESULT)_stubs.o $(RESULT)_stubs.cc

top:
	ocamlfind ocamlmktop  -thread -package $(PACKS),$(RESULT_PACKAGE) -linkpkg -o $(RESULT_PACKAGE).top

uninstall::
	ocamlfind remove  $(RESULT_PACKAGE)

install:: META
	ocamlfind install  $(RESULT_PACKAGE) META $(CMI) $(RESULT).cma $(RESULT).cmxa $(RESULT).a lib$(RESULT).a dll$(RESULT).so

META: META.pl
	./META.pl > META

clean::
	rm -f META *.a *.cma *.cmi *.cmo *.cmx *.cmxa *.o *.so \
		$(RESULT).ml $(RESULT).mli $(RESULT).top \
		$(RESULT)_stubs.c $(RESULT)_stubs.c.ORIG $(RESULT)_stubs.cc $(RESULT_PACKAGE).top \
		rocksffi.ml rocksffi.cc rocksffi.o
