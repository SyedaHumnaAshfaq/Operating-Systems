
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
int AvailableTicket = 10;
pthread_cond_t ticketBookerCond;
pthread_cond_t ticketCheckerCond;
pthread_mutex_t mutex;
void *ticketBooker(void *arg)
{
    int *ticket = (int *)arg;
    pthread_mutex_lock(&mutex);
    while(AvailableTicket == 0)
    {
        pthread_cond_wait(&ticketBookerCond,&mutex);
    }
    AvailableTicket--;
    printf("Ticket %d is booked by ticket booker = %d\n",AvailableTicket,*ticket);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&ticketCheckerCond);
    return (NULL);
}
void *ticketChecker(void *arg)
{
    int *ticket = (int *)arg;
    pthread_mutex_lock(&mutex);
    while(AvailableTicket == 10)
    {
        pthread_cond_wait(&ticketCheckerCond,&mutex);
    }
    AvailableTicket++;
    printf("Ticket %d is checked by ticket checker = %d\n",AvailableTicket,*ticket);
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&ticketBookerCond);
    return (NULL);
}
int main()
{
    pthread_t tid[20];
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&ticketBookerCond,NULL);
    pthread_cond_init(&ticketCheckerCond,NULL);
    int ticket[20];
    for(int i=0;i<20;i++)
    {
        ticket[i] = i+1;
    }
    for(int i=0;i<20;i++)
    {
        if(i%2 == 0)
        {
            pthread_create(&tid[i],NULL,ticketBooker,&ticket[i]);
        }
        else
        {
            pthread_create(&tid[i],NULL,ticketChecker,&ticket[i]);
        }
    }
    for(int i=0;i<20;i++)
    {
        pthread_join(tid[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&ticketBookerCond);
    pthread_cond_destroy(&ticketCheckerCond);
    return 0;
}