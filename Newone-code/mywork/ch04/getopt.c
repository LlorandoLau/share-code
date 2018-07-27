#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	char opt;
	while((opt=getopt(argc,argv,":if:jik"))!=-1)
		printf("%c\n",opt);
}