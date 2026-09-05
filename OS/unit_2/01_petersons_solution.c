#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>

atomic_bool flag[2];
atomic_int turn;
int shared = 0;

void enter_region(int i)
{
    int j = 1 - i;
    atomic_store(&flag[i], true);
    atomic_store(&turn, j);
    while (atomic_load(&flag[j]) && atomic_load(&turn) == j) { }
}

void leave_region(int i)
{
    atomic_store(&flag[i], false);
}

void *worker(void *arg)
{
    int i = *(int *)arg;
    for (int k = 0; k < 100000; k++) {
        enter_region(i);
        shared++;
        leave_region(i);
    }
    return NULL;
}

int main(void)
{
    atomic_init(&flag[0], false);
    atomic_init(&flag[1], false);
    atomic_init(&turn, 0);

    pthread_t t[2];
    int id[2] = {0, 1};

    pthread_create(&t[0], NULL, worker, &id[0]);
    pthread_create(&t[1], NULL, worker, &id[1]);

    pthread_join(t[0], NULL);
    pthread_join(t[1], NULL);

    printf("shared = %d\n", shared);
    return 0;
}
