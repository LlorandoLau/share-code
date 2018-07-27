#include "header.h"

int main(int argc, char const *argv[])
{
	int shmid;
	int running=1;
	void* shared_memory=(void*)0;
	struct shared_used_st* shared_buf;

	srand((unsigned int)getpid());

	shmid=shmget((key_t)1234,sizeof(struct shared_used_st),0666| IPC_CREAT);

	shared_memory=shmat(shmid,(void*)0,0);
	printf("Memory attached at %X\n", (int)shared_memory);
	shared_buf=(struct shared_used_st*)shared_memory;
	shared_buf->signal=0;
	while(running)
	{
		if(shared_buf->signal)
		{
			printf("You wrote %s", shared_buf->message);
			sleep(rand()%4);
			shared_buf->signal=0;
			if(strncmp(shared_buf->message,"end",3)==0)
			{
				running=0;
			}
		}
	}
	shmdt(shared_memory);
	shmctl(shmid,IPC_RMID,0);
	return 0;
}