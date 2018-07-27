#include "header.h"
int main(int argc, char const *argv[])
{
	/* code */
	FILE* fd;
	char buf[BUFSIZ+1];
	int char_read;
	int result;
	memset(buf,'\0',sizeof(buf));

	fd=popen("ls","r");
	if(fd==NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	char_read=fread(buf,sizeof(char),BUFSIZ,fd);
	if(char_read>0)
	{
		printf("Output was:*\n%s\n",buf );
	}
	pclose(fd);
	exit(EXIT_SUCCESS);

}