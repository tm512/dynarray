CC=cc
AR=ar
RANLIB=ranlib
OPT=2
DBG=0

.PHONY: default clean

default: libdynarray.a

dynarray.o: dynarray.c dynarray.h
	$(CC) -O$(OPT) -g$(DBG) -c dynarray.c -o dynarray.o

libdynarray.a: dynarray.o
	ar cru libdynarray.a dynarray.o
	ranlib libdynarray.a

example: libdynarray.a
	$(CC) -O$(OPT) -g$(DBG) -c example.c -o example.o
	$(CC) example.o libdynarray.a -o example

clean:
	@echo Cleaning...
	@rm -f libdynarray.a
	@rm -f dynarray.o
	@rm -f example
	@rm -f example.o
