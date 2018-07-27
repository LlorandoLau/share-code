#include "header.h"
int main(int argc, char const *argv[])
{
	/* code */
	pthread_t a_thread[10];
	int i;
	int res;
	for(i=0;i<10;i++)
	{
		res=pthread_create(&(a_thread[i]),NULL,thread_func,(void*)&i);
		displayError(res);
		// sleep(1);
	}

	for(i=9;i>=0;i--)
	{
		res=pthread_join(a_thread[i],NULL);
	}
	return 0;
}

void* thread_func(void * args){
	int number=*(int*)args;
	printf("This is Num.%d thread\n",number	);
	int random=1+(int)(9.0*rand()/(RAND_MAX+1.0));
	// printf("Thread%d: I would sleep %ds\n",number,random);
	// sleep(random);
	printf("\tBye from Num.%d thread\n", number);
	pthread_exit(0);
}