#include "header.h"

void* thread_func(void* args);
int thread_finished=0;
int main()
{
	pthread_t a_thread;
	void* thread_result;
	pthread_attr_t thread_attr;
	int res;
	res=pthread_attr_init(&thread_attr);
	if(res!=0)
	{
		fprintf(stderr, "Attribute creation failed\n");
		exit(EXIT_FAILURE);
	}
	res=pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED);
	if(res!=0)
	{
		fprintf(stderr, "Error: %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	res=pthread_create(&a_thread,NULL,thread_func,NULL);
	if(res!=0)
	{
		fprintf(stderr, "Error: %s\n",strerror(errno));
		exit(EXIT_FAILURE);
	}
	(void)pthread_attr_destroy(&thread_attr);
	while(!thread_finished)
	{
		printf("Waiting for the thread to end\n");
		sleep(1);
	}
	printf("Is end\n");
	exit(EXIT_SUCCESS);
}
void* thread_func(void * args)
{
	sleep(4);
	thread_finished=1;
	pthread_exit(NULL);

}