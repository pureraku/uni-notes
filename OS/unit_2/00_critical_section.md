# 00 — Critical Section

The exam pattern is:

> **Entry → Critical Section → Exit → Remainder**

A critical section is the part of a program that accesses shared data.

```mermaid
flowchart LR
    A[Entry section] --> B[Critical section]
    B --> C[Exit section]
    C --> D[Remainder section]
    D --> A
```

## Actual C example

```c
#include <stdio.h>
#include <pthread.h>

int shared = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg)
{
    for (int i = 0; i < 100000; i++) {

        /* ENTRY SECTION */
        pthread_mutex_lock(&lock);

        /* CRITICAL SECTION */
        shared++;

        /* EXIT SECTION */
        pthread_mutex_unlock(&lock);

        /* REMAINDER SECTION */
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
    return 0;
}
```

Compile:

```bash
gcc 00_critical_section.c -pthread
```

**One-liner:** Protect the shared-data part with synchronization so only permitted threads/processes enter it.
