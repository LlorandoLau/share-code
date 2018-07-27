#include "apue.h"

int
main(int argv,char* argc[])
{
	if(argv<2)	err_sys("Please enter the dir name");
	if (chdir(argc[1]) < 0)
		err_sys("chdir failed");
	printf("chdir to %s succeeded\n",argc[1]);
	exit(0);
}
