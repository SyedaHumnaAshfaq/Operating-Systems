#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
int arr[20]={1,2,3,4,5,6,7,8,9,10,11,12,14,13,15,16,18,20,30,44};
int totalsum=0;
void *sum(void *arg){

int target=(int)arg;
int t= *target;
for(int i=t; i<t+10;i++)
{
totalsum+=arr[i];

}




}
int main(){
pthread_t thread1;
pthread_t thread2;
int target=0;

pthread_create(&thread1,NULL,sum, (void*)&target);

pthread_create(&thread2,NULL,sum, (void*)&target);

target=target+15;

pthread_join(thread1,NULL);
pthread_join(thread2,NULL);

printf("%d", totalsum);







}