#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t isEmpty;
pthread_cond_t isFull;
int bufferindex;
int buffer[5];


void *consumer(void *arg)
{
 
    for(int i = 0;i<5;i++)
    {
        pthread_mutex_lock(&mutex);
        while(bufferindex==0)
        pthread_cond_wait(&isEmpty,&mutex);
        buffer[bufferindex]=0;
        printf("Consuming");
        bufferindex--;
        pthread_cond_signal(&isFull);
        pthread_mutex_unlock(&mutex);
    }
    


    
    pthread_exit(NULL);

}
void *producer(void *arg)
{
    for(int i = 0;i < 5; i++)
    {
        pthread_mutex_lock(&mutex);
        while(bufferindex==5)
        pthread_cond_wait(&isFull,&mutex);
        buffer[bufferindex]=1;
        printf("Producing");
        bufferindex++;
        pthread_cond_signal(&isEmpty);
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);

}

int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&isEmpty,NULL);
    pthread_cond_init(&isFull,NULL);
    //function of threads
    pthread_t thread1;
    pthread_t thread2;
   
    pthread_create(&thread1,NULL,producer,NULL);
    pthread_create(&thread2,NULL,consumer,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&isEmpty);
    pthread_cond_destroy(&isFull);
}