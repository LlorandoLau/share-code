#include "header.h"
int main(int argc, char const *argv[])
{
	char buffer[BUFSIZ];
	int shmid;
	int running=1;
	void* shared_memory=(void*)0;
	struct shared_used_st* shared_buf;

	srand((unsigned int)getpid());

	shmid=shmget((key_t)1234,sizeof(struct shared_used_st),0666|IPC_CREAT);

	shared_memory=shmat(shmid,(void*)0,0);
	printf("Memory attached at %X\n",(int)shared_memory );

	shared_buf=(struct shared_used_st*)shared_memory;

	while(running)
	{
		while(shared_buf->signal==1)
		{
			sleep(1);
			printf("Waiting for client\n");
		}
		printf("Enter some text: ");
		fgets(buffer,BUFSIZ,stdin);
		
		strncpy(shared_buf->message,buffer,TEXT_SZ);
		shared_buf->signal=1;

		if(strncmp(buffer,"end",3)==0)
		{
			running=0;
		}
	}

	shmdt(shared_memory);
	return 0;
}