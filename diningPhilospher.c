#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define SIZE 5

pthread_mutex_t chopstick[SIZE];
pthread_cond_t cond[SIZE];

void *philosopher(void *arg)
{
    int philosopherId = *(int *)arg;
    int left = philosopherId;
    int right = (philosopherId + 1) % SIZE;

    while (1)
    {
        printf("Philosopher %d is thinking\n", philosopherId);

        // Attempt to acquire left chopstick
        pthread_mutex_lock(&chopstick[left]);

        // Attempt to acquire right chopstick
        pthread_mutex_lock(&chopstick[right]);

        // Both chopsticks acquired, philosopher is eating
        printf("Philosopher %d is eating\n", philosopherId);

        // Release both chopsticks
        pthread_mutex_unlock(&chopstick[right]);
        pthread_mutex_unlock(&chopstick[left]);

        sleep(1); // Simulating eating time

        // Wait for a moment before thinking again
        printf("Philosopher %d finished eating\n", philosopherId);
        usleep(1000);

        // Use condition variable to synchronize access to chopsticks
        pthread_cond_wait(&cond[left], &chopstick[left]);
        pthread_cond_wait(&cond[right], &chopstick[right]);
    }
}

int main()
{
    pthread_t tid[SIZE];
    int i;

    // Initialize mutexes and condition variables
    for (i = 0; i < SIZE; i++)
    {
        pthread_mutex_init(&chopstick[i], NULL);
        pthread_cond_init(&cond[i], NULL);
    }

    // Create philosopher threads
    for (i = 0; i < SIZE; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i;
        pthread_create(&tid[i], NULL, philosopher, id);
    }

    // Wait for philosopher threads to finish
    for (i = 0; i < SIZE; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // Destroy mutexes and condition variables
    for (i = 0; i < SIZE; i++)
    {
        pthread_mutex_destroy(&chopstick[i]);
        pthread_cond_destroy(&cond[i]);
    }

    return 0;
}
