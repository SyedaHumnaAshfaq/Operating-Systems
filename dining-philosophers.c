#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define LEFT(i) ((i) + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS
#define RIGHT(i) ((i) + 1) % NUM_PHILOSOPHERS

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond[NUM_PHILOSOPHERS];
    int state[NUM_PHILOSOPHERS];
} DiningData;

DiningData diningData;

void init(DiningData* data) {
    pthread_mutex_init(&data->mutex, NULL);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_init(&data->cond[i], NULL);
        data->state[i] = 0; // 0 indicates philosopher is thinking
    }
}

void pickup_chopsticks(int philosopher) {
    pthread_mutex_lock(&diningData.mutex);
    diningData.state[philosopher] = 1; // 1 indicates philosopher is hungry
    test(philosopher);
    if (diningData.state[philosopher] != 2) { // 2 indicates philosopher is eating
        pthread_cond_wait(&diningData.cond[philosopher], &diningData.mutex);
    }
    pthread_mutex_unlock(&diningData.mutex);
}

void return_chopsticks(int philosopher) {
    pthread_mutex_lock(&diningData.mutex);
    diningData.state[philosopher] = 0; // 0 indicates philosopher is thinking
    test(LEFT(philosopher));
    test(RIGHT(philosopher));
    pthread_mutex_unlock(&diningData.mutex);
}

void test(int philosopher) {
    if (diningData.state[philosopher] == 1 && diningData.state[LEFT(philosopher)] != 2 &&
        diningData.state[RIGHT(philosopher)] != 2) {
        diningData.state[philosopher] = 2; // 2 indicates philosopher is eating
        pthread_cond_signal(&diningData.cond[philosopher]);
    }
}

void* philosopher(void* arg) {
    int philosopher = *((int*)arg);
    int eatingTime = rand() % 3 + 1;

    printf("Philosopher %d is thinking.\n", philosopher);
    sleep(1);

    pickup_chopsticks(philosopher);

    printf("Philosopher %d is eating for %d seconds.\n", philosopher, eatingTime);
    sleep(eatingTime);

    return_chopsticks(philosopher);

    printf("Philosopher %d finished eating.\n", philosopher);

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philIds[NUM_PHILOSOPHERS];

    init(&diningData);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        philIds[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &philIds[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
