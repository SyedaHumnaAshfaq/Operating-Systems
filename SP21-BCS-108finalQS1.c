#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<time.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sched.h>


int matrixA[4][4] = {{1,1,1,1},{1,1,1,1},{1,1,1,1},{1,1,1,1}};
int matrixB[4][4] = {{2,2,2,2},{2,2,2,2},{2,2,2,2},{2,2,2,2}};
int matrixC[4][4];
void *row1(void *arg)
{
    
    int sum = 0;
    for(int i=0;i<4;i++)
    {
        sum = matrixA[0][i] + matrixB[0][i];
        matrixC[0][i] = sum;
        printf("%d",matrixC[0][i]);
    }
    printf("\n");
    return (NULL);
}
void * row2(void *arg)
{
    int sum = 0;
    for(int i=0;i<4;i++)
    {
        sum = matrixA[1][i] + matrixB[1][i];
        matrixC[1][i] = sum;
         printf("%d",matrixC[1][i]);
    }
     printf("\n");
    return (NULL);
}
void * row3(void *arg)
{
    
    int sum = 0;
    for(int i=0;i<4;i++)
    {
        sum = matrixA[2][i] + matrixB[2][i];
        matrixC[2][i] = sum;
         printf("%d",matrixC[2][i]);
    }
    printf("\n");
    return (NULL);
}
void * row4(void *arg)
{
    

    int sum = 0;
    for(int i=0;i<4;i++)
    {
        sum = matrixA[3][i] + matrixB[3][i];
        matrixC[3][i] = sum;
        printf("%d",matrixC[3][i]);
    }
     printf("\n");
   return (NULL);
}
int main()
{
    pthread_t tid1,tid2,tid3,tid4;
    
    pthread_create(&tid1,NULL,row1,NULL);
    pthread_create(&tid2,NULL,row2,NULL);
    pthread_create(&tid3,NULL,row3,NULL);
    pthread_create(&tid4,NULL,row4,NULL);
    // for(int i=0;i<4;i++)
    // {
    //     for(int j=0;j<4;j++)
    //     {
    //         printf("%d ",matrixC[i][j]);
    //     }
    //     printf("\n");
    // }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    pthread_join(tid4,NULL);
    
}