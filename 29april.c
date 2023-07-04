#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#define buffersize 5
int array[buffersize];
int bufferindex = 0;
pthread_mutex_t mutex;
//this code is written to produce 5 items and then consume 5 items. producer and consumer are not running parallely so we use conditional
//variables in other task(code is written on register)
void * producer()
{
    pthread_mutex_lock(&mutex);
   
    while(bufferindex<buffersize)
        {
            array[bufferindex]=1;
            printf("%d",array[bufferindex]);
            printf("Producing");
            bufferindex++;
        }
    if(bufferindex==buffersize)
    {pthread_mutex_unlock(&mutex);
    bufferindex--;}

}
void *consumer()
{
    if(bufferindex>0)
      pthread_mutex_lock(&mutex);
    while(bufferindex>=0)
    {
        array[bufferindex] = -1;
         printf("%d",array[bufferindex]);
         printf("Consuming");
        bufferindex--;
    }
    if(bufferindex<0)
    pthread_mutex_unlock(&mutex);

}

int main()
{
   pthread_mutex_init(&mutex,NULL);
   pthread_t thread1;
   pthread_t thread2;
   
    pthread_create(&thread1,NULL,producer,NULL);
    pthread_create(&thread2,NULL,consumer,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    

    pthread_mutex_destroy(&mutex);
}

