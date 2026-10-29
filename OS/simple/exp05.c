/* Experiment 5: Reader-Writer Problem */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define READERS 3

static sem_t resource;
static pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;
static int readers = 0;
static int value = 0;

static void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&count_lock);
    readers++;
    if (readers == 1)
        sem_wait(&resource);
    pthread_mutex_unlock(&count_lock);

    printf("Reader %d reads value %d\n", id, value);

    pthread_mutex_lock(&count_lock);
    readers--;
    if (readers == 0)
        sem_post(&resource);
    pthread_mutex_unlock(&count_lock);
    return NULL;
}

static void *writer(void *arg)
{
    (void)arg;
    sem_wait(&resource);
    value++;
    printf("Writer changes value to %d\n", value);
    sem_post(&resource);
    return NULL;
}

int main(void)
{
    pthread_t read_threads[READERS], write_thread;
    int ids[READERS];

    if (sem_init(&resource, 0, 1) != 0) {
        perror("sem_init");
        return 1;
    }
    for (int i = 0; i < READERS; i++) {
        ids[i] = i + 1;
        if (pthread_create(&read_threads[i], NULL, reader, &ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    if (pthread_create(&write_thread, NULL, writer, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }
    for (int i = 0; i < READERS; i++)
        pthread_join(read_threads[i], NULL);
    pthread_join(write_thread, NULL);

    sem_destroy(&resource);
    pthread_mutex_destroy(&count_lock);
    return 0;
}
