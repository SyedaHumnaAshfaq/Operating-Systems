#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
int array[1];
pthread_mutex_t mutex;
void * producer()
{
    pthread_mutex_lock(&mutex);
    array[0]=1;
    printf("Producing");
    pthread_mutex_unlock(&mutex);
}
void *consumer()
{
    pthread_mutex_lock(&mutex);
    array[0]=-1;
    printf("Consuming");
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

