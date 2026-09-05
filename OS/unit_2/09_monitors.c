#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define ITEMS 20

typedef struct {
    int buffer[BUFFER_SIZE];
    int in, out, count;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} BufferMonitor;

void monitor_init(BufferMonitor *m)
{
    m->in = m->out = m->count = 0;
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
