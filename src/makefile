OUT = dragonfly
VERSION ?= 0.3.0
DATADIR ?= /usr/share

DEFINES := -DVERSION=\"${VERSION}\"

CC = gcc
PKGDEPS = gtk+-2.0 webkit-1.0
CFLAGS := -g -Wall $(shell pkg-config --cflags ${PKGDEPS}) ${DEFINES}
LDFLAGS := $(shell pkg-config --libs ${PKGDEPS})

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: dragonfly

dragonfly: $(OBJ)
	@echo CC -o dragonfly 
	@$(CC) $(OBJ) $(LDFLAGS) -o ${OUT}

browser.o: browser.c browser.h
	@echo CC -c browser.c
	@$(CC) -c $(CFLAGS) browser.c

callback.o: callback.c callback.h
	@echo CC -c callback.c
	@$(CC) -c $(CFLAGS) callback.c

config.o: config.c config.h
	@echo CC -c config.c
	@$(CC) -c $(CFLAGS) config.c
	
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

searchengine.o: searchengine.c searchengine.h
	@echo CC -c searchengine.c
	@$(CC) -c $(CFLAGS) searchengine.c
	
toolbar.o: toolbar.c toolbar.h
	@echo CC -c toolbar.c
	@$(CC) -c $(CFLAGS) toolbar.c
	
utils.o: utils.c utils.h
	@echo CC -c utils.c
	@$(CC) -c $(CFLAGS) utils.c
	
clean:
	@echo cleaning
	@${RM} $(OBJ) ${OUT}

strip: all
	@strip --strip-all ${OUT}

.PHONY: all clean debug strip
