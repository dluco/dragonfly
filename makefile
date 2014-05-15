VERSION=0.3

CC=gcc
CFLAGS=-g -Wall $(shell pkg-config --cflags gtk+-2.0 webkit-1.0) -DVERSION=\"${VERSION}\"
LDFLAGS+=$(shell pkg-config --libs gtk+-2.0 webkit-1.0)

OBJ=browser.o callback.o main.o menu.o toolbar.o

all: dragonfly

dragonfly: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o dragonfly

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

callback.o: callback.c callback.h
	$(CC) -c $(CFLAGS) callback.c

browser.o: browser.c browser.h
	$(CC) -c $(CFLAGS) browser.c
	
menu.o: menu.c menu.h
	$(CC) -c $(CFLAGS) menu.c
	
toolbar.o: toolbar.c toolbar.h
	$(CC) -c $(CFLAGS) toolbar.c
	
clean:
	rm -rf $(OBJ) dragonfly
	
.PHONY: all clean
