//write a c program that has two functions one for reader and one for writer and use mutex locks to synchronize them, don't use semaphores
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sched.h>
#include<pthread.h>
pthread_mutex_t mutex;
pthread_cond_t reader;
pthread_cond_t writer;
int readercount = 0;
int writercount = 0;

void * reader1()
{
    pthread_mutex_lock(&mutex);
    readercount++;
    if(writercount>0)
    {
        printf("reader cannot read when the writer is writing");
        pthread_cond_wait(&reader,&mutex);
    }
    // pthread_mutex_unlock(&mutex);
    printf("Reader is reading");
    // pthread_mutex_lock(&mutex);
    readercount--;
    if(readercount==0)
    pthread_cond_signal(&writer);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
void * writer1()
{
    pthread_mutex_lock(&mutex);
    writercount++;
    if(readercount>0)
    {
        printf("writer cannot write when the reader is reading");
        pthread_cond_wait(&writer,&mutex);
    }
    // pthread_mutex_unlock(&mutex);
    printf("Writer is writing");
    // pthread_mutex_lock(&mutex);
    writercount--;
    if(writercount==0)
    pthread_cond_signal(&reader);
    pthread_mutex_unlock(&mutex);
    return NULL;
}
int main()
{
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&reader,NULL);
    pthread_cond_init(&writer,NULL);
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1,NULL,reader1,NULL);
    pthread_create(&thread2,NULL,writer1,NULL);
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&reader);
    pthread_cond_destroy(&writer);
    return 0;
}



