all: thread2 thread3  thread4 pthread_attr thread_cancel multithread

thread2: thread2.c
	gcc -D_REENTRANT -I/usr/include/nptl thread2.c -o thread2 -L/usr/lib/nptl -lpthread

thread3: thread3.c
	gcc -D_REENTRANT -I/usr/include/nptl thread3.c -o thread3 -L/usr/lib/nptl -lpthread

mutex: mutex.c
	gcc -D_REENTRANT -I/usr/include/nptl mutex.c -o mutex -L/usr/lib/nptl -lpthread

thread4: thread4.c
	gcc -D_REENTRANT -I/usr/include/nptl thread4.c -o thread4 -L/usr/lib/nptl -lpthread

pthread_attr: pthread_attr.c
	gcc -D_REENTRANT -I/usr/include/nptl pthread_attr.c -o pthread_attr -L/usr/lib/nptl -lpthread

thread_cancel: thread_cancel.c
	gcc -D_REENTRANT -I/usr/include/nptl thread_cancel.c -o thread_cancel -L/usr/lib/nptl -lpthread

multithread: multithread.c
	gcc -D_REENTRANT -I/usr/include/nptl multithread.c -o multithread -L/usr/lib/nptl -lpthread