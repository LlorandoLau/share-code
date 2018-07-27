#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/msg.h>

#define TEXT_SZ 2048
#define MAX_TEXT 512
struct shared_used_st
{
	int signal;
	char message[TEXT_SZ];
};

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

struct msg_st
{
	long int msg_type;
	char message[BUFSIZ];
};