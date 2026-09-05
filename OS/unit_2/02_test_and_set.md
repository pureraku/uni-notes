# 02 — Test-and-Set

`test_and_set()` is an **atomic hardware-style operation** used to build a lock.

## Actual C code using C11 atomics

```c
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_flag lock = ATOMIC_FLAG_INIT;
int shared = 0;

void acquire_lock(void)
{
    while (atomic_flag_test_and_set_explicit(
               &lock, memory_order_acquire)) {
        /* busy wait */
    }
}

void release_lock(void)
{
    atomic_flag_clear_explicit(&lock, memory_order_release);
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
gcc 02_test_and_set.c -pthread -std=c11
```

Core exam pattern:

```c
while (test_and_set(&lock))
    ;
```

**One-liner:** Atomically test the old lock value and set the lock; if it was already set, keep spinning.
