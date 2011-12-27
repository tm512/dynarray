CC=cc
AR=ar
RANLIB=ranlib
OPT=2
DBG=0
DEST=/usr/local/lib
OUT=libdynarray.a

.PHONY: default clean install

default: $(OUT)

dynarray.o: dynarray.c dynarray.h
	$(CC) -O$(OPT) -g$(DBG) -c dynarray.c -o dynarray.o

$(OUT): dynarray.o
	$(AR) cru $(OUT) dynarray.o
	$(RANLIB) $(OUT)

example: libdynarray.a
	$(CC) -O$(OPT) -g$(DBG) -c example.c -o example.o
	$(CC) example.o $(OUT) -o example

install: libdynarray.a
	mv libdynarray.a $(DEST)/

clean:
	@echo Cleaning...
	@rm -f $(OUT) dynarray.o example example.o
