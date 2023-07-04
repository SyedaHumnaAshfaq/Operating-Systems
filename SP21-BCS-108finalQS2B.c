
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

pthread_mutex_t mutex;
pthread_cond_t truckCond;
pthread_cond_t carCond;
int truckCount = 0;
int carCount = 0;
void *truck(void *arg)
{
    int *truck = (int *)arg;
    pthread_mutex_lock(&mutex);
    
    while(truckCount == 1 || carCount == 3)
    {
        pthread_cond_wait(&truckCond,&mutex);
    }
    truckCount++;
    printf("Truck %d is crossing the bridge\n",*truck);
    truckCount--;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&carCond);
    return (NULL);
}
void *car(void *arg)
{
    int *car = (int *)arg;
    pthread_mutex_lock(&mutex);
    
    while(carCount==3 || truckCount==1)
    {
        pthread_cond_wait(&carCond,&mutex);
    }
    if (carCount<3 && truckCount==0)
    {
        pthread_cond_signal(&truckCond);
    }
    carCount++;
    printf("Car %d is crossing the bridge\n",*car);
    //carCount--;
    if(carCount == 3)
    {
        carCount = 0;
    }
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&truckCond);
    return (NULL);
}
int main()
{
    pthread_t tid[20];
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&truckCond,NULL);
    pthread_cond_init(&carCond,NULL);
    int vehicle[20];
    for(int i=0;i<20;i++)
    {
        vehicle[i] = i+1;
    }
    for(int i=0;i<20;i++)
    {
        if(i%2 == 0)
        {
            pthread_create(&tid[i],NULL,truck,&vehicle[i]);
        }
        else
        {
            pthread_create(&tid[i],NULL,car,&vehicle[i]);
        }
    }
    for(int i=0;i<20;i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&truckCond);
    pthread_cond_destroy(&carCond);
    return 0;
}
