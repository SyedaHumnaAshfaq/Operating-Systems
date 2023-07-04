#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
#include<sched.h>
//to run : gcc filename.c -lpthread -o output
//write a multithreaded program that search a specific integer in an array of size 20
int array [20] = {1,2,3,4,5,8,4,7,5,9,7,2,6,4,7,2,8,1,8,0};
void * find(void * arg)
{
    int value1 = *(int *)arg;
    printf("%d\n",value1);
    //printf("hello";)
    int k ; 
    for( k = value1;k<=value1+10;k++)
    {
        //printf("hello");
        if(array[k] == 0 )
        {
            printf("0 was found at %d",k);
            break;
        }
    }
    return NULL;

}
int main()
{
    
   int i = 0;
    //int j = 10;
      pthread_t threadid1;
    for (i=0;i<11; i=i+10){
       // pthread_t threadid1;
        pthread_create(&threadid1,NULL,find,(void *)&i);
         pthread_join(threadid1,NULL);
         
        }
    
   return 0;
  
    //pthread_join(threadid2,NULL);


}