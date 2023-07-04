#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_CHAIRS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t customerReady = PTHREAD_COND_INITIALIZER;
pthread_cond_t barberReady = PTHREAD_COND_INITIALIZER;

int numCustomers = 0;
int numFreeChairs = NUM_CHAIRS;
int barberStatus = 0; // 0 - sleeping, 1 - ready to cut hair

void *barber(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);

        // Check if there are no customers
        if (numCustomers == 0)
        {
            printf("Barber is sleeping\n");
            barberStatus = 0; // Sleeping
            pthread_cond_wait(&customerReady, &mutex);
        }

        // Serve the next customer
        printf("Barber is cutting hair\n");
        numCustomers--;
        numFreeChairs++;

        // Signal the customer that the barber is ready
        pthread_cond_signal(&barberReady);
        pthread_mutex_unlock(&mutex);

        // Simulate cutting hair
        sleep(2);
    }
}

void *customer(void *arg)
{
    int customerId = *(int *)arg;
    pthread_mutex_lock(&mutex);

    // Check if there are free chairs
    if (numFreeChairs > 0)
    {
        printf("Customer %d is sitting in the waiting room\n", customerId);
        numCustomers++;
        numFreeChairs--;

        // Signal barber that a customer is ready
        pthread_cond_signal(&customerReady);
        pthread_mutex_unlock(&mutex);

        // Wait for barber to be ready
        pthread_mutex_lock(&mutex);
        while (barberStatus != 1)
        {
            pthread_cond_wait(&barberReady, &mutex);
        }
        pthread_mutex_unlock(&mutex);

        // Get haircut
        printf("Customer %d is getting a haircut\n", customerId);
    }
    else
    {
        printf("No free chairs available for customer %d. Leaving...\n", customerId);
        pthread_mutex_unlock(&mutex);
    }
}

int main()
{
    pthread_t barberThread, customerThreads[NUM_CHAIRS];
    int i, customerIds[NUM_CHAIRS];

    // Create barber thread
    pthread_create(&barberThread, NULL, barber, NULL);

    // Create customer threads
    for (i = 0; i < NUM_CHAIRS; i++)
    {
        customerIds[i] = i + 1;
        pthread_create(&customerThreads[i], NULL, customer, &customerIds[i]);
        sleep(1); // Spacing out the customer arrivals
    }

    // Wait for all customer threads to finish
    for (i = 0; i < NUM_CHAIRS; i++)
    {
        pthread_join(customerThreads[i], NULL);
    }

    // Cancel the barber thread
    pthread_cancel(barberThread);
    pthread_join(barberThread, NULL);

    return 0;
}
