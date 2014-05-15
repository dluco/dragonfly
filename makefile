VERSION=0.3

CC=gcc
CFLAGS=-g -Wall $(shell pkg-config --cflags gtk+-2.0 webkit-1.0) -DVERSION=\"${VERSION}\"
LDFLAGS+=$(shell pkg-config --libs gtk+-2.0 webkit-1.0)

OBJ=main.o browser.o callback.o

all: dragonfly

dragonfly: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o dragonfly

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

callback.o: callback.c
	$(CC) -c $(CFLAGS) callback.c

browser.o: browser.c
	$(CC) -c $(CFLAGS) browser.c
	
clean:
	rm -rf $(OBJ) dragonfly
	
.PHONY: all clean
