all : write read copy_test stat fcopy readdir error mmap
CC=gcc

write: write.c
	$(CC) -o write write.c

read: read.c
	${CC} -o read read.c

copy_test: copy_test.c
	${CC} -o copy_test copy_test.c

stat: stat.c
	${CC} -o stat stat.c

fcopy: fcopy.c
	${CC} -o fcopy fcopy.c

readdir: readdir.c
	${CC} -o readdir readdir.c

error: error.c
	${CC} -o error error.c

mmap: mmap.c
	${CC} -o mmap mmap.c