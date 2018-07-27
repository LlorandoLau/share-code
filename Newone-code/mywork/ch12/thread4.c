#include "header.h"
#define SIZE 1024

pthread_mutex_t work_mutex;
char work_area[SIZE];
int time_to_exit=0;

void *thread_func(void* args);

int main()
{
	void* thread_result;
	pthread_t a_thread;
	int res;
	res=pthread_mutex_init(&work_mutex,NULL);	//NULL位置设置的是互斥量的属性
	if(res!=0)
	{
		fprintf(stderr, "Failed to create mutex\n");
		exit(EXIT_FAILURE);
	}

	res=pthread_create(&a_thread,NULL,thread_func,NULL);
	if(res!=0)
	{
		fprintf(stderr, "Failed to create pthread\n");
		exit(EXIT_FAILURE);
	}

	pthread_mutex_lock(&work_mutex);
	printf("Here begin\n");
	while(!time_to_exit)
	{
		fgets(work_area,SIZE,stdin);
		pthread_mutex_unlock(&work_mutex);
		while(1)
		{
			pthread_mutex_lock(&work_mutex);
			if(work_area[0]!='\0')
			{
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
			}else{
				break;
			}
		}
	}
	pthread_mutex_unlock(&work_mutex);
	printf("\nWaiting for thread to finish...\n");
	res=pthread_join(a_thread,&thread_result);
	if(res!=0)
	{
		fprintf(stderr, "Failed to join pthread\n");
		exit(EXIT_FAILURE);
	}
	printf("Thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	exit(EXIT_SUCCESS);
}

void* thread_func(void* arg)
{
	sleep(1);
	pthread_mutex_lock(&work_mutex);
	while(strncmp("end",work_area,3)!=0)
	{
		printf("You input %lu char\n",strlen(work_area)-1 );
		work_area[0]='\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		while(work_area[0]=='\0')
		{
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
	}
	time_to_exit=1;
	work_area[0]='\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}