#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4
#define ITERATIONS 100000

long counter = 0;
sem_t mutex;

void *increment(void *arg)
{
    (void)arg;

    for (int i = 0; i < ITERATIONS; i++) {
        /* Enter critical section */
        sem_wait(&mutex);

        counter++;

        /* Leave critical section */
        sem_post(&mutex);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];

    if (sem_init(&mutex, 0, 1) != 0) {
        perror("sem_init");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment, NULL) != 0) {
            perror("pthread_create");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Expected counter = %d\n", NUM_THREADS * ITERATIONS);
    printf("Actual counter   = %ld\n", counter);

    sem_destroy(&mutex);

    return EXIT_SUCCESS;
}
