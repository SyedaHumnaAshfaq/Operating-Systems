#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main()
{
    int arraywaiting[5]= {0,0,0,0,0};
    int arrayBurst[4] = {2,3,6,1};
    int arrayThroughput[4] = {0,0,0,0}; 
    //int temp;
    for (int step = 1; step < 4; step++) 
    {

        int key = arrayBurst[step];
        int j = step - 1;
        while (key < arrayBurst[j] && j >= 0) {
        arrayBurst[j + 1] = arrayBurst[j];
        --j;
    }
    arrayBurst[j + 1] = key;
  }
  
  for(int i = 1 ; i<=4 ; i++)
    {
        arraywaiting[i] = arrayBurst[i-1]+ arraywaiting[i-1];
        arrayThroughput[i-1] = arrayBurst[i-1] + arraywaiting[i-1];
    }
    
    printf(" %d      \n", arrayBurst[0]);

    printf("BurstTime  Waiting Time   ThroughPut \n");
 for(int i=0; i<4 ; i++)
   {
    printf(" %d                %d                %d  \n",arrayBurst[i],arraywaiting[i],arrayThroughput[i]);  }
   
}
