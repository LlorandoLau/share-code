#include "header.h"
int main()
{
	int fd[2];
	int fork_result;
	int write_or_read_chars;
	const char data[]="123";
	char buf[BUFSIZ+1];

	memset(buf,'\0',sizeof(buf));
	if(pipe(fd)==0)
	{
		fork_result=fork();
		if(fork_result==0){
			write_or_read_chars=write(fd[1],data,strlen(data));
			printf("Process %d Write %d char\n", getpid(),write_or_read_chars);
		}else{
			sprintf(buf,"%d",fd[0]);
			execl("pipe4","pipe4",buf,(char*)0);
			fprintf(stderr, "%s\n", strerror(errno));
			exit(0);
	}
		exit(0);
	}
	exit(1);
}