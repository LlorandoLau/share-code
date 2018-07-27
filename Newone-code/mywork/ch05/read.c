#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buf[128];
	int nread;

	nread=read(0,buf,128);
	if(nread==-1)
		write(2,"A read error has occurred\n",26);
	else if(nread==0)
		write(2,"A write error has occurred\n",27);

	exit(0);
}