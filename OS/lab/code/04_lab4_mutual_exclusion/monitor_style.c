#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define CAPACITY 5
#define ITEMS 10

/*
 * Monitor-style bounded buffer:
 * - mutex protects shared state
 * - condition variables coordinate when the buffer is full/empty
 */

int buffer[CAPACITY];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

void put(int value)
{
    pthread_mutex_lock(&lock);

    while (count == CAPACITY) {
        pthread_cond_wait(&not_full, &lock);
    }

    buffer[in] = value;
    in = (in + 1) % CAPACITY;
    count++;

    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&lock);
}

int get(void)
{
    int value;

    pthread_mutex_lock(&lock);

    while (count == 0) {
        pthread_cond_wait(&not_empty, &lock);
    }

    value = buffer[out];
    out = (out + 1) % CAPACITY;
    count--;

    pthread_cond_signal(&not_full);
    pthread_mutex_unlock(&lock);

    return value;
}

void *producer(void *arg)
{
    (void)arg;

    for (int i = 1; i <= ITEMS; i++) {
        put(i);
        printf("Produced %d\n", i);
    }

    return NULL;
}

void *consumer(void *arg)
{
    (void)arg;

    for (int i = 1; i <= ITEMS; i++) {
        int value = get();
        printf("Consumed %d\n", value);
        usleep(10000);
    }

    return NULL;
}

int main(void)
{
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);

    return EXIT_SUCCESS;
}
