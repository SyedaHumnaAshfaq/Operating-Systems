#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>


void * hello(void* arg) //void type pointer(always void because create only takes void type function)
{
    printf("hello world %ld",pthread_self());
    return NULL; //because void type function so return NULL

}
int main()
{
   pthread_t threadid; //datatype
   pthread_create(&threadid,NULL,hello,NULL); //arguments:variable,attributes,function call(what will the thread do),parameters of function
   pthread_join(threadid,NULL); //program does not exit until all threads completed because of this. every thread has it's own join...same work as wait in process
}

