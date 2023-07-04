#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
//make 2 threads,first thread should take an array of size 10,second thread should sort the array

int number[5];
void * takeArray()
{
    printf("enter numbers");
    
    for(int i = 0;i<5;i++)
    {
        scanf("%d",&number[i]);
    }
    return NULL;

}
void * sort()
{
    int size = sizeof(number) / sizeof(number[0]);

     int i, key, j;
    for (i = 1; i < 5; i++) {
        key = number[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are
        // greater than key, to one position ahead
        // of their current position
        while (j >= 0 && number[j] > key) {
            number[j + 1] = number[j];
            j = j - 1;
        }
        number[j + 1] = key;
    }

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", number[i]);
    }
    printf("\n");
    return NULL;


}

int main()
{
   pthread_t threadid1; //datatype
   pthread_create(&threadid1,NULL,takeArray,NULL);
   pthread_join(threadid1,NULL);
   pthread_t threadid2; //datatype
   pthread_create(&threadid2,NULL,sort,NULL);
   
   pthread_join(threadid2,NULL);

}