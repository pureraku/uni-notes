#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

atomic_bool lock = false;
int shared = 0;

void swap_bool(atomic_bool *a, bool *b)
{
    bool old = atomic_exchange(a, *b);
    *b = old;
}

void acquire_lock(void)
{
    bool key = true;
    while (key == true)
        swap_bool(&lock, &key);
}

void release_lock(void)
{
    atomic_store(&lock, false);
}

void *worker(void *arg)
{
    for (int i = 0; i < 100000; i++) {
        acquire_lock();
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
