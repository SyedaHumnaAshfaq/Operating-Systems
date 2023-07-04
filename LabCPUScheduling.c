#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
    int arraywaiting[4]= {0,0,0,0};
    int arrayBurst[4] = {2,3,6,1};
    int arrayThroughput[4] = {0,0,0,0}; 
    for(int i = 1;i<=4;i++)
    {
        arraywaiting[i] = arrayBurst[i-1]+arraywaiting[i-1];
        arrayThroughput[i-1] = arrayBurst[i-1] + arraywaiting[i-1];
    }
    printf("Process No.  Waiting Time   ThroughPut \n");
    for(int i = 0;i<4;i++)
    {
        printf("%d                   %d               %d \n",i+1,arraywaiting[i],arrayThroughput[i]);
    }

}
