#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);
int run_row=1;
char message[] = "Hello World";

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    int count1=0;

    res = pthread_create(&a_thread, NULL, thread_function, (void *)message);
    
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Waiting for thread to finish...\n");

    while(count1<20)
    {
        if(run_row==1)
        {
            printf("Is main func: %d\n",1);
            run_row=2;
            count1++;
        }else{
            sleep(0.5);
        }
    }
    res = pthread_join(a_thread, &thread_result);
    
    if (res != 0) {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
    
    exit(EXIT_SUCCESS);
}

void *thread_function(void *arg) {
    int count2=0;
    while(count2<20)
    {
        if(run_row==2)
        {
            printf("Is thread_func: %d\n",2);
            run_row=1;
            count2++;
        }else{
            sleep(1);
        }
    }
}
