/* Experiment 3: Multithreading */
#include <pthread.h>
#include <stdio.h>

#define THREADS 3

static int counter = 0;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    printf("Thread %d finished 1000 increments.\n", id);
    return NULL;
}

int main(void)
{
    pthread_t threads[THREADS];
    int ids[THREADS];

    for (int i = 0; i < THREADS; i++) {
        ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, worker, &ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < THREADS; i++)
        pthread_join(threads[i], NULL);

    printf("Final counter: %d (expected 3000)\n", counter);
    pthread_mutex_destroy(&lock);
    return 0;
}
