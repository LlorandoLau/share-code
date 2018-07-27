#include "head.h"
int main()
{
	int in=open("a.txt",O_RDONLY);
	if(in<0)	printf("%s\n", strerror(errno));

	char * str=mmap(0,1024,PROT_READ,MAP_SHARED,in,0);
	printf("%s\n",str );

	if(str==MAP_FAILED)
		printf("Failed to open this item\n");
	printf("%s\n", strerror(errno));
}