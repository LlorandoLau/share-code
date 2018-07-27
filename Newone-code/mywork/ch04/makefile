all: getopt showenv environ envtime limits thread1

getopt: getopt.c
	gcc -o getopt getopt.c

showenv: showenv.c
	gcc -o showenv showenv.c

test: test.cpp
	g++ -o test test.cpp

environ: environ.c
	gcc -o environ environ.c

envtime: envtime.c
	gcc -o envtime envtime.c

limits: limits.c
	gcc -o limits limits.c

thread1: thread1.c
	gcc -D_REENTRANT -I/usr/include/nptl thread1.c -o thread1 -L/usr/lib/nptl -lpthread