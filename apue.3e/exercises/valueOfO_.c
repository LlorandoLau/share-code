#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "apue.h"
#include <stdlib.h>
int main()
{
	char str[25];
	itoa(O_APPEND,str,2);
	printf("%d %d %d %d\n", O_RDONLY,O_WRONLY,O_RDWR,O_ACCMODE);
	printf("%s %d %d\n",str,O_NONBLOCK,O_SYNC);
	return 0;
}