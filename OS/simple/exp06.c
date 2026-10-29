/* Experiment 6: Dining Philosophers Problem */
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define PHILOSOPHERS 5

static sem_t forks[PHILOSOPHERS];
static sem_t room;

static void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % PHILOSOPHERS;

    printf("Philosopher %d is thinking.\n", id + 1);
    sem_wait(&room); /* At most four compete for forks, preventing deadlock. */
    sem_wait(&forks[left]);
    sem_wait(&forks[right]);
    printf("Philosopher %d is eating.\n", id + 1);
    sem_post(&forks[right]);
    sem_post(&forks[left]);
    sem_post(&room);
    return NULL;
}

int main(void)
{
    pthread_t threads[PHILOSOPHERS];
    int ids[PHILOSOPHERS];

    if (sem_init(&room, 0, PHILOSOPHERS - 1) != 0) {
        perror("sem_init");
        return 1;
    }
    for (int i = 0; i < PHILOSOPHERS; i++) {
        if (sem_init(&forks[i], 0, 1) != 0) {
            perror("sem_init");
            return 1;
        }
        ids[i] = i;
    }
    for (int i = 0; i < PHILOSOPHERS; i++) {
        if (pthread_create(&threads[i], NULL, philosopher, &ids[i]) != 0) {
            perror("pthread_create");
            return 1;
        }
    }
    for (int i = 0; i < PHILOSOPHERS; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < PHILOSOPHERS; i++)
        sem_destroy(&forks[i]);
    sem_destroy(&room);
    return 0;
}
