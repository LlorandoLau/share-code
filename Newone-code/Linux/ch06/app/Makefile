
all:curses_app

#Uncomment and edit the line below if necessary
#CFLAGS=-I/usr/include/ncurses
CC=gcc
INCLUDE=/usr/include/ncurses
LDFLAGS=-lncurses


curses_app:curses_app.c
	${CC} -I$(INCLUDE) curses_app.c -o curses_app $(LDFLAGS)