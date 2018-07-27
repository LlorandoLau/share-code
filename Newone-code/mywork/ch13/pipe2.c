#include "header.h"
int main()
{
	int fd[2];
	int fork_result;
	int write_or_read_chars;
	const char data[]="123";
	char buf[BUFSIZ+1];
	printf("%d\n", BUFSIZ);

	memset(buf,'\0',sizeof(buf));
	if(pipe(fd)==0)
	{
		fork_result=fork();
		if(fork_result==0){
			write_or_read_chars=write(fd[1],data,strlen(data));
			printf("Process%d Write %d char\n", getpid(),write_or_read_chars);
		}else{
			write_or_read_chars=read(fd[0],buf,BUFSIZ);
			printf("Process%d Read %d chars\n",getpid(), write_or_read_chars);
	}
		exit(0);
	}
	exit(1);
}