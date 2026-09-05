# 06 — Producer–Consumer / Bounded Buffer

The course setup is:

```text
full  = 0
empty = n
mutex = 1
```

`full` counts occupied slots, `empty` counts free slots, and `mutex` protects the buffer.

## Actual C code

```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define ITEMS 20

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void *producer(void *arg)
{
    for (int item = 1; item <= ITEMS; item++) {

        /* produce item */

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);
    }

    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 0; i < ITEMS; i++) {

        sem_wait(&full);
        sem_wait(&mutex);

        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        printf("Consumed %d\n", item);
    }

    return NULL;
}

int main(void)
{
    pthread_t producer_thread, consumer_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
```

Compile:

```bash
gcc 06_producer_consumer.c -pthread
```

## Memorize this order

Producer:

```c
wait(empty);
wait(mutex);

/* add */

signal(mutex);
signal(full);
```

Consumer:

```c
wait(full);
wait(mutex);

/* remove */

signal(mutex);
signal(empty);
```

**One-liner:** Producer needs an empty slot; consumer needs a full slot; mutex protects the buffer.

$$
full + empty = BUFFER\_SIZE
$$
