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
    int arrayArrival[4] = {0,4,5,2};

     for (int step = 1; step < 4; step++) 
    {

        int key = arrayArrival[step];
        int j = step - 1;
        while (key < arrayArrival[j] && j >= 0) {
        arrayArrival[j + 1] = arrayArrival[j];
        --j;
    }
    arrayArrival[j + 1] = key;
  }
//   for (int i=0;i<4;i++)
//   {
//     printf("%d",arrayArrival[i]);
//   }
    


}