#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 4
#define WRITERS 2

int data = 0;
int readcount = 0;
sem_t mutex, rw_mutex;

void *reader(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++) {
        sem_wait(&mutex);
        readcount++;
        if (readcount == 1)
            sem_wait(&rw_mutex);
        sem_post(&mutex);

        printf("Reader %d reads %d\n", id, data);
        usleep(50000);

        sem_wait(&mutex);
        readcount--;
        if (readcount == 0)
            sem_post(&rw_mutex);
        sem_post(&mutex);

        usleep(50000);
    }
    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < 3; i++) {
        sem_wait(&rw_mutex);
        data++;
        printf("Writer %d writes %d\n", id, data);
        usleep(100000);
        sem_post(&rw_mutex);
        usleep(50000);
    }
    return NULL;
}

int main(void)
{
    pthread_t readers[READERS], writers[WRITERS];
    int reader_id[READERS], writer_id[WRITERS];

    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    for (int i = 0; i < READERS; i++) {
        reader_id[i] = i;
        pthread_create(&readers[i], NULL, reader, &reader_id[i]);
    }

    for (int i = 0; i < WRITERS; i++) {
        writer_id[i] = i;
        pthread_create(&writers[i], NULL, writer, &writer_id[i]);
    }

    for (int i = 0; i < READERS; i++)
        pthread_join(readers[i], NULL);

    for (int i = 0; i < WRITERS; i++)
        pthread_join(writers[i], NULL);

    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);
    return 0;
}
