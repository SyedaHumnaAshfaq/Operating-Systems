#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<pthread.h>
//write a program that forms a calculator with basic functions (+,-,*,/),each function is to be performed by a different thread. Take two global operators.

void * addition()
{
    int a,b,sum;
    scanf("%d",&a);
    scanf("%d",&b);
    sum = a+b;
    printf("sum= %d",sum);
    return NULL;

}

void * subtraction()
{
    int a,b,subtract;
    scanf("%d",&a);
    scanf("%d",&b);
    subtract = a-b;
    printf("subtract= %d",subtract);
    return NULL;

}
void * multiplication()
{
    int a,b,product;
    scanf("%d",&a);
    scanf("%d",&b);
    
    product = a*b;
    printf("product= %d",product);
    return NULL;

}
void * division()
{
    int a,b,divide;
    scanf("%d",&a);
    scanf("%d",&b);
    
    divide = a/b;
    printf("divide= %d",divide);
    return NULL;
} 

int main()


{
   pthread_t threadid1; //datatype
   
//    pthread_t threadid2; //datatype

//    pthread_t threadid3; //datatype
  
//    pthread_t threadid4;  //datatype
   int choice;
   scanf("%d", &choice);
   if(choice == 1)
   {
    pthread_create(&threadid1,NULL,addition,NULL);
   }
   else if(choice == 2)
   {
    pthread_create(&threadid1,NULL,subtraction,NULL);

   }
   else if(choice==3)
   {
     pthread_create(&threadid1,NULL,multiplication,NULL);
    
   }
   else if(choice==4)
   {
     pthread_create(&threadid1,NULL,division,NULL);
    
   }
   pthread_join(threadid1,NULL);
//    pthread_join(threadid2,NULL);
//    pthread_join(threadid3,NULL);
//    pthread_join(threadid4,NULL); 
   return 0;
}