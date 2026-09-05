# 03 — Swap-Based Lock

The textbook synchronization-hardware idea is an atomic `swap()` between a shared lock and a local key.

## Actual C code

```c
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_bool lock = false;
int shared = 0;

void swap_bool(atomic_bool *a, bool *b)
{
    bool old = atomic_exchange_explicit(
        a, *b, memory_order_acq_rel);

    *b = old;
}

void acquire_lock(void)
{
    bool key = true;

    while (key == true) {
        swap_bool(&lock, &key);
    }
}

void release_lock(void)
{
    atomic_store_explicit(&lock, false, memory_order_release);
}

void *worker(void *arg)
{
    for (int i = 0; i < 100000; i++) {
        acquire_lock();

        /* CRITICAL SECTION */
        shared++;

        release_lock();
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
gcc 03_swap_lock.c -pthread -std=c11
```

Exam pattern:

```c
key = true;

while (key == true)
    swap(&lock, &key);
```

**One-liner:** Atomically exchange `lock` and a local `key` until the caller obtains the lock.
