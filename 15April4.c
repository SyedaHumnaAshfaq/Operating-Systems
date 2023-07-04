#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
#include<sched.h>
//write a program in c in which user enter n make two threads. one thread will print odd values upto that no,on thread will return even value
int n;
void * odd()
{
    for(int i = 0;i<n;i++)
    {
        if(i/2!=0)
        {
            printf("%d",i);
            sched_yield();
        }

    }
return NULL;

}
void * even()
{
    for(int i = 0; i<n ;i++)
    {
        if(i/2==0)
        {
            printf("%d",i);
            sched_yield();//to forcefully context switch
        }

    }
return NULL;

}
int main()
{
    scanf("%d",&n);
    pthread_t threadid1;
    pthread_create(&threadid1,NULL,odd,NULL);
    
    pthread_t threadid2;
    pthread_create(&threadid2,NULL,even,NULL);
    pthread_join(threadid1,NULL);
    pthread_join(threadid2,NULL);
    
}