# 04 — Mutex Lock

A mutex is the simple **one-at-a-time lock**.

## Actual C code

```c
#include <stdio.h>
#include <pthread.h>

int shared = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg)
{
    for (int i = 0; i < 100000; i++) {

        pthread_mutex_lock(&lock);

        /* CRITICAL SECTION */
        shared++;

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("shared = %d\n", shared);

    pthread_mutex_destroy(&lock);
    return 0;
}
```

Compile:

```bash
gcc 04_mutex_lock.c -pthread
```

Exam pattern:

```c
do {
    acquire(lock);

    /* CRITICAL SECTION */

    release(lock);
} while (TRUE);
```

**One-liner:** Lock before shared-data access; unlock immediately after.
