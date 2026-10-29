/* Experiment 4: Mutual Exclusion Using Semaphore and Monitor */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define PEOPLE 4

static sem_t room;
static pthread_mutex_t monitor = PTHREAD_MUTEX_INITIALIZER;
static int inside = 0;

static void *person(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&room);
    pthread_mutex_lock(&monitor);
    inside++;
    printf("Person %d enters; people inside: %d\n", id, inside);
    pthread_mutex_unlock(&monitor);

    sleep(1); /* Hold the room permit briefly so overlap is visible. */
    pthread_mutex_lock(&monitor);
    inside--;
    printf("Person %d leaves; people inside: %d\n", id, inside);
    pthread_mutex_unlock(&monitor);
    sem_post(&room);
    return NULL;
}

int main(void)
{
    pthread_t threads[PEOPLE];
    int ids[PEOPLE];

    if (sem_init(&room, 0, 2) != 0) {
        perror("sem_init");
        return 1;
    }
    for (int i = 0; i < PEOPLE; i++) {
        ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, person, &ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < PEOPLE; i++)
        pthread_join(threads[i], NULL);

    sem_destroy(&room);
    pthread_mutex_destroy(&monitor);
    return 0;
}
