VERSION=0.3

CC=gcc
CFLAGS=-g -Wall $(shell pkg-config --cflags gtk+-2.0 webkit-1.0) -DVERSION=\"${VERSION}\"
LDFLAGS+=$(shell pkg-config --libs gtk+-2.0 webkit-1.0)

OBJ=about.o browser.o callback.o cookie.o dialog.o download.o main.o menu.o search.o toolbar.o utils.o

all: dragonfly

dragonfly: $(OBJ)
	@echo CC -o dragonfly 
	@$(CC) $(OBJ) $(LDFLAGS) -o dragonfly

about.o: about.c about.h
	@echo CC -c about.c
	@$(CC) -c $(CFLAGS) about.c

browser.o: browser.c browser.h
	@echo CC -c browser.c
	@$(CC) -c $(CFLAGS) browser.c

callback.o: callback.c callback.h
	@echo CC -c callback.c
	@$(CC) -c $(CFLAGS) callback.c
	
cookie.o: cookie.c cookie.h
	@echo CC -c cookie.c
	@$(CC) -c $(CFLAGS) cookie.c
	
dialog.o: dialog.c dialog.h
	@echo CC -c dialog.c
	@$(CC) -c $(CFLAGS) dialog.c
	
download.o: download.c download.h
	@echo CC -c download.c
	@$(CC) -c $(CFLAGS) download.c
	
main.o: main.c
	@echo CC -c main.c
	@$(CC) -c $(CFLAGS) main.c
	
menu.o: menu.c menu.h
	@echo CC -c menu.c
	@$(CC) -c $(CFLAGS) menu.c
	
search.o: search.c search.h
	@echo CC -c search.c
	@$(CC) -c $(CFLAGS) search.c
	
toolbar.o: toolbar.c toolbar.h
	@echo CC -c toolbar.c
	@$(CC) -c $(CFLAGS) toolbar.c
	
utils.o: utils.c utils.h
	@echo CC -c utils.c
	@$(CC) -c $(CFLAGS) utils.c
	
clean:
	@echo cleaning
	@rm -rf $(OBJ) dragonfly
	
.PHONY: all clean
