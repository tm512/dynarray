CC=cc
AR=ar
RANLIB=ranlib
OPT=2
DBG=0
DEST=/usr/local/lib

.PHONY: default clean install

default: libdynarray.a

dynarray.o: dynarray.c dynarray.h
	$(CC) -O$(OPT) -g$(DBG) -c dynarray.c -o dynarray.o

libdynarray.a: dynarray.o
	ar cru libdynarray.a dynarray.o
	ranlib libdynarray.a

example: libdynarray.a
	$(CC) -O$(OPT) -g$(DBG) -c example.c -o example.o
	$(CC) example.o libdynarray.a -o example

install: libdynarray.a
	mv libdynarray.a $(DEST)/

clean:
	@echo Cleaning...
	@rm -f libdynarray.a
	@rm -f dynarray.o
	@rm -f example
	@rm -f example.o
