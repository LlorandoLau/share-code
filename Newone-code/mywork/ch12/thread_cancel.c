#include "header.h"
int main()
{
	/*
	在运行时候中断，并且等待运行结束。
	和前面的，脱离线程，不用再等待，而不必设置不同
	*/
	int res;
	pthread_t a_thread;
	void * thread_result;

	res=pthread_create(&a_thread,NULL,thread_func,NULL);
	displayError(res);

	sleep(2);

	res=pthread_cancel(a_thread);
	displayError(res);

	res=pthread_join(a_thread,NULL);
	displayError(res);

	exit(EXIT_SUCCESS);
}

void* thread_func(void* args)
{
	int i,res;

	res=pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	displayError(res);

	res=pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED,NULL);
	displayError(res);

	printf("Now is running\n");
	for(int i=0;i<1000;i++)
	{
		printf("Look me: %d\n",i );
		sleep(1);
	}
	pthread_exit(0);
}