#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define MEALS 3

sem_t forks[N];

/*
 * At most N-1 philosophers may try to acquire forks at once.
 * This prevents the simple situation where every philosopher
 * holds one fork and waits forever for the second.
 */
sem_t room;

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    for (int meal = 1; meal <= MEALS; meal++) {
        printf("Philosopher %d is thinking.\n", id);
        usleep(50000);

        sem_wait(&room);

        sem_wait(&forks[left]);
        printf("Philosopher %d picked fork %d.\n", id, left);

        sem_wait(&forks[right]);
        printf("Philosopher %d picked fork %d.\n", id, right);

        printf("Philosopher %d is eating (meal %d).\n", id, meal);
        usleep(70000);

        sem_post(&forks[right]);
        sem_post(&forks[left]);

        sem_post(&room);

        printf("Philosopher %d released both forks.\n", id);
    }

    return NULL;
}

int main(void)
{
    pthread_t threads[N];
    int ids[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }

    sem_destroy(&room);

    return EXIT_SUCCESS;
}
