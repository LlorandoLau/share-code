
all: ipmode moveadd pad screen1 color keypad multiw1 subscl test

#Uncomment and edit the line below if necessary
#CFLAGS=-I/usr/include/ncurses
CC=gcc
INCLUDE=/usr/include/ncurses
LDFLAGS=-lncurses


ipmode:ipmode.c
	${CC} -I$(INCLUDE) ipmode.c -o ipmode $(LDFLAGS)

moveadd:moveadd.c
	${CC} -I$(INCLUDE)	moveadd.c -o moveadd $(LDFLAGS)

pad:pad.c
	${CC} -I$(INCLUDE) pad.c -o pad $(LDFLAGS)

screen1:screen1.c
	${CC} -I$(INCLUDE) screen1.c -o screen1 $(LDFLAGS)

color:color.c 
	${CC} -I$(INCLUDE) color.c -o color $(LDFLAGS)

keypad:keypad.c
	${CC} -I$(INCLUDE) keypad.c -o keypad $(LDFLAGS)

multiw1:multiw1.c
	${CC} -I$(INCLUDE) multiw1.c -o multiw1 $(LDFLAGS)

subscl:subscl.c
	${CC} -I$(INCLUDE) subscl.c -o  subscl $(LDFLAGS)

test:test.c
	${CC} -I$(INCLUDE) test.c -o  test $(LDFLAGS)
