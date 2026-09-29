#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2
#define READ_LOOPS 3
#define WRITE_LOOPS 3

int shared_data = 0;
int read_count = 0;

sem_t resource;   /* Controls access to shared_data */
sem_t read_mutex; /* Protects read_count */

void *reader(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < READ_LOOPS; i++) {
        /* Update reader count safely. */
        sem_wait(&read_mutex);

        read_count++;

        /* First reader locks the resource for all readers. */
        if (read_count == 1) {
            sem_wait(&resource);
        }

        sem_post(&read_mutex);

        /* Multiple readers may execute this part together. */
        printf("Reader %d reads value %d\n", id, shared_data);
        usleep(50000);

        /* Leaving reader section. */
        sem_wait(&read_mutex);

        read_count--;

        /* Last reader releases the resource. */
        if (read_count == 0) {
            sem_post(&resource);
        }

        sem_post(&read_mutex);

        usleep(30000);
    }

    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < WRITE_LOOPS; i++) {
        sem_wait(&resource);

        shared_data++;
        printf("Writer %d writes value %d\n", id, shared_data);

        sem_post(&resource);

        usleep(80000);
    }

    return NULL;
}

int main(void)
{
    pthread_t readers[READERS];
    pthread_t writers[WRITERS];

    int reader_ids[READERS];
    int writer_ids[WRITERS];

    sem_init(&resource, 0, 1);
    sem_init(&read_mutex, 0, 1);

    for (int i = 0; i < READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (int i = 0; i < WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource);
    sem_destroy(&read_mutex);

    return EXIT_SUCCESS;
}
