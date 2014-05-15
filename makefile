VERSION=0.3

CC=gcc
CFLAGS=-g -Wall $(shell pkg-config --cflags gtk+-2.0 webkit-1.0) -DVERSION=\"${VERSION}\"
LDFLAGS+=$(shell pkg-config --libs gtk+-2.0 webkit-1.0)

OBJ=browser.o callback.o main.o menu.o toolbar.o

all: dragonfly

dragonfly: $(OBJ)
	@echo CC -o dragonfly 
	@$(CC) $(OBJ) $(LDFLAGS) -o dragonfly

main.o: main.c
	@echo CC -c main.c
	@$(CC) -c $(CFLAGS) main.c

callback.o: callback.c callback.h
	@echo CC -c callback.c
	@$(CC) -c $(CFLAGS) callback.c

browser.o: browser.c browser.h
	@echo CC -c browser.c
	@$(CC) -c $(CFLAGS) browser.c
	
menu.o: menu.c menu.h
	@echo CC -c menu.c
	@$(CC) -c $(CFLAGS) menu.c
	
toolbar.o: toolbar.c toolbar.h
	@echo CC -c toolbar.c
	@$(CC) -c $(CFLAGS) toolbar.c
	
clean:
	@echo cleaning
	@rm -rf $(OBJ) dragonfly
	
.PHONY: all clean
