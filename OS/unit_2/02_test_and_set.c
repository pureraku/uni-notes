#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_flag lock = ATOMIC_FLAG_INIT;
int shared = 0;

void acquire_lock(void)
{
    while (atomic_flag_test_and_set_explicit(&lock, memory_order_acquire)) { }
}

void release_lock(void)
{
    atomic_flag_clear_explicit(&lock, memory_order_release);
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
