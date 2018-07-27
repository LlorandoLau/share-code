#include "header.h"
int main(int argc, char const *argv[])
{
	int descri;
	char buf[8192];

	sscanf(argv[1],"%d",&descri);
	memset(buf,'\0',sizeof(buf));
	int read_chars=read(descri,buf,sizeof(buf));

	printf("Process %d read %d chars\n", getpid(),read_chars);
	return 0;
}