# 05 — Semaphores

A semaphore is a synchronization counter.

- `wait(S)` → decrement / acquire a permit
- `signal(S)` → increment / release a permit

## Actual C code with POSIX semaphores

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t S;
int shared = 0;

void *worker(void *arg)
{
    for (int i = 0; i < 100000; i++) {

        sem_wait(&S);

        /* CRITICAL SECTION */
        shared++;

        sem_post(&S);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    sem_init(&S, 0, 1);

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("shared = %d\n", shared);

    sem_destroy(&S);
    return 0;
}
```

Compile:

```bash
gcc 05_semaphores.c -pthread
```

Exam pseudocode:

```c
wait(S)
{
    while (S <= 0)
        ;
    S--;
}

signal(S)
{
    S++;
}
```

**One-liner:** `wait()` takes a permit; `signal()` gives one back.

> Real POSIX `sem_wait()` blocks instead of spinning, unlike the simplified textbook pseudocode.
