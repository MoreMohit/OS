#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define TOTAL_ITEMS 15

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t full, empty;
pthread_mutex_t mutex;

void *producer(void *args) {
    for (int i = 0; i < TOTAL_ITEMS / 3; i++) {
        int item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %ld produced: %d\n", (long)args, item);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return NULL;
}

void *consumer(void *args) {
    for (int i = 0; i < TOTAL_ITEMS / 3; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
                printf("Consumer %ld consumed: %d\n", (long)args, item);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return NULL;
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t prod[3], cons[3];
    for (long i = 0; i < 3; i++) {
        pthread_create(&prod[i], NULL, producer, (void *)i);
        pthread_create(&cons[i], NULL, consumer, (void *)i);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
