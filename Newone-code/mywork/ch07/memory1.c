#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 1024*1024
int main()
{
	char * memory;
	int size=SIZE;
	int exit_code=EXIT_FAILURE;

	memory=(char*)malloc(size);
	if(memory!=NULL)
	{
		sprintf(memory,"Hello world\n");
		printf("%s\n",memory );
		exit_code=EXIT_SUCCESS;
	}
	exit(exit_code);
}