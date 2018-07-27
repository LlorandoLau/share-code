#include "header.h"
void *thread_func(void* arg);
char message[]="Never try to ";
int main(int num,char* arr)
{
	//线程标识符
	pthread_t a_thread;
	int res;
	void* result;

	res=pthread_create(&a_thread,NULL,thread_func,(void*)message);
	if(res!=0)
	{
		perror("Thread was not start");
		exit(EXIT_FAILURE);
	}
	pthread_join(a_thread,&result);
	printf("message after func: %s\n", 	message);
	printf("message return from thread%s\n", (char*)result);

}

void *thread_func(void* arg)
{
	printf("Arg of this thread is %s\n",(char*)arg );
	sleep(3);
	strcpy(message,"Bye");
	pthread_exit("Here is the return val");
}