#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define BUFFER_SIZE 5

pthread_mutex_t mutex;
pthread_cond_t full;
pthread_cond_t empty;
int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

void *producer(void *arg) {
    int item = 1;

    while (1) {
        pthread_mutex_lock(&mutex);
        
        // Wait if buffer is full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&empty, &mutex);
        }

        buffer[in] = item;
        printf("Producer produced item %d\n", item);
        item++;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        // Signal that buffer is not empty
        pthread_cond_signal(&full);
        
        pthread_mutex_unlock(&mutex);

        sleep(1); // Simulate producer producing items
    }

    return NULL;
}

void *consumer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        
        // Wait if buffer is empty
        while (count == 0) {
            pthread_cond_wait(&full, &mutex);
        }

        int item = buffer[out];
        printf("Consumer consumed item %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        count--;

        // Signal that buffer is not full
        pthread_cond_signal(&empty);
        
        pthread_mutex_unlock(&mutex);

        sleep(2); // Simulate consumer consuming items
    }

    return NULL;
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full, NULL);
    pthread_cond_init(&empty, NULL);
    pthread_t producer_thread;
    pthread_t consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full);
    pthread_cond_destroy(&empty);

    return 0;
}
