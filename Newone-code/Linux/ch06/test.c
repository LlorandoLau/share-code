#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	initscr();
	const chtype a=123;
	move(5,15);
	addch(a);
	refresh();
	endwin();
	exit(EXIT_SUCCESS);
}