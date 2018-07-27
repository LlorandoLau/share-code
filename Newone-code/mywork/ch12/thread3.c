#include "header.h"
void thread_func(void* args);
sem_t bin_sem;
char buf[256];
int main(int argc, char const *argv[])
{
	int res=sem_init(&bin_sem,0,0);
	pthread_t a_thread;
	void* result;

	if(res!=0)
	{
		fprintf(stderr, "Failed to init sem\n");
		exit(EXIT_FAILURE);
	}

	res=pthread_create(&a_thread,NULL,thread_func,buf);
	if(res!=0)
	{
		fprintf(stderr, "Failed to create pthread\n");
		exit(EXIT_FAILURE);
	}

	while(strncmp("end",buf,3)!=0){
		fgets(buf,256,stdin);
		sem_post(&bin_sem);
	}
	pthread_join(a_thread,&result);
	sem_destroy(&bin_sem);
	exit(0);
	return 0;
}

void thread_func(void* args)
{
	sem_wait(&bin_sem);
	while(strncmp("end",buf,3)!=0){
		printf("You have input %d char\n",strlen(buf)-1 );
		sem_wait(&bin_sem);
	}
}