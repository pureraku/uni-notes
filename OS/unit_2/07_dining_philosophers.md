# 07 — Dining Philosophers

Five philosophers share five chopsticks/forks.

The basic semaphore solution is:

```c
wait(left);
wait(right);

/* EAT */

signal(left);
signal(right);
```

The important problem: if everyone gets one fork first, everyone can wait forever for the second.

## Actual C code — basic semaphore version

```c
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
```

Compile:

```bash
gcc 07_dining_philosophers.c -pthread
```

**One-liner:** Multiple processes need multiple shared resources; careless acquisition can produce deadlock.

## Deadlock pattern to recognize

```text
P0: holds F0 → wants F1
P1: holds F1 → wants F2
P2: holds F2 → wants F3
P3: holds F3 → wants F4
P4: holds F4 → wants F0
```

The basic code above demonstrates the textbook resource-acquisition pattern; an actual run may or may not enter deadlock depending on scheduling.
