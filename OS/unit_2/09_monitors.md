# 09 — Monitors

C has no built-in `monitor` construct like the textbook pseudocode, so the closest real POSIX-C implementation uses:

- `pthread_mutex_t` for mutual exclusion
- `pthread_cond_t` for condition variables
- `pthread_cond_wait()` for `x.wait()`
- `pthread_cond_signal()` for `x.signal()`

## Actual C monitor-style code

```c
#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define ITEMS 20

typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} BufferMonitor;

void monitor_init(BufferMonitor *m)
{
    m->in = 0;
    m->out = 0;
    m->count = 0;

    pthread_mutex_init(&m->mutex, NULL);
    pthread_cond_init(&m->not_full, NULL);
    pthread_cond_init(&m->not_empty, NULL);
}

void insert(BufferMonitor *m, int item)
{
    pthread_mutex_lock(&m->mutex);

    while (m->count == BUFFER_SIZE)
        pthread_cond_wait(&m->not_full, &m->mutex);

    m->buffer[m->in] = item;
    m->in = (m->in + 1) % BUFFER_SIZE;
    m->count++;

    pthread_cond_signal(&m->not_empty);
    pthread_mutex_unlock(&m->mutex);
}

int remove_item(BufferMonitor *m)
{
    pthread_mutex_lock(&m->mutex);

    while (m->count == 0)
        pthread_cond_wait(&m->not_empty, &m->mutex);

    int item = m->buffer[m->out];
    m->out = (m->out + 1) % BUFFER_SIZE;
    m->count--;

    pthread_cond_signal(&m->not_full);
    pthread_mutex_unlock(&m->mutex);

    return item;
}

void *producer(void *arg)
{
    BufferMonitor *m = arg;

    for (int i = 1; i <= ITEMS; i++)
        insert(m, i);

    return NULL;
}

void *consumer(void *arg)
{
    BufferMonitor *m = arg;

    for (int i = 0; i < ITEMS; i++)
        printf("Consumed %d\n", remove_item(m));

    return NULL;
}

int main(void)
{
    BufferMonitor monitor;
    pthread_t p, c;

    monitor_init(&monitor);

    pthread_create(&p, NULL, producer, &monitor);
    pthread_create(&c, NULL, consumer, &monitor);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    pthread_mutex_destroy(&monitor.mutex);
    pthread_cond_destroy(&monitor.not_full);
    pthread_cond_destroy(&monitor.not_empty);

    return 0;
}
```

Compile:

```bash
gcc 09_monitors.c -pthread
```

Textbook mapping:

```text
monitor shared data     → struct fields
monitor procedure       → C function
monitor mutual exclusion→ pthread_mutex_t
condition x             → pthread_cond_t
x.wait()                → pthread_cond_wait()
x.signal()              → pthread_cond_signal()
```

**One-liner:** A monitor packages shared data, operations, and synchronization together so access is controlled.

> Important exam distinction: the syntax `monitor { ... }` is textbook/pseudocode; POSIX C implements the same idea with mutexes and condition variables.
