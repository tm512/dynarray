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

clean:
	@echo Cleaning...
	@rm libdynarray.a
	@rm dynarray.o
