#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t S;
int shared = 0;

void *worker(void *arg)
{
    for (int i = 0; i < 100000; i++) {
        sem_wait(&S);
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
