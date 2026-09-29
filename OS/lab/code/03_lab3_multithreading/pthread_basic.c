#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

void *worker(void *arg)
{
    int id = *(int *)arg;

    printf("Thread %d is running.\n", id);

    return NULL;
}

int main(void)
{
    pthread_t threads[NUM_THREADS];
    int ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        ids[i] = i + 1;

        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            perror("pthread_create failed");
            return EXIT_FAILURE;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join failed");
            return EXIT_FAILURE;
        }
    }

    printf("All threads have completed.\n");

    return EXIT_SUCCESS;
}
