#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
long open_max(void);
int main(int argc,char* argv[])
{
	long equal=open_max();
	printf("%ld\n", equal);
	return 0;
}