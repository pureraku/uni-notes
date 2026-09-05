#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
sem_t chopstick[N];

void *philosopher(void *arg)
{
    int i = *(int *)arg;
    int left = i;
    int right = (i + 1) % N;

    for (int round = 0; round < 3; round++) {
        printf("Philosopher %d is thinking\n", i);
        usleep(100000);

        sem_wait(&chopstick[left]);
        sem_wait(&chopstick[right]);

        printf("Philosopher %d is eating\n", i);
        usleep(100000);

        sem_post(&chopstick[left]);
        sem_post(&chopstick[right]);
    }
    return NULL;
}

int main(void)
{
    pthread_t threads[N];
    int id[N];

    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(threads[i], NULL);

    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);

    return 0;
}
