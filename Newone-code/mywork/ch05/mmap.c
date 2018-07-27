#include "head.h"
int main()
{
	int in=fopen("a.txt","r");
	struct stat buf;
	fstat(in,&buf);

	char * str=(char*)mmap(0,buf.st_size,PROT_READ|PROT_WRITE,MAP_SHARED,in,0);
	printf("%s\n",str );
}