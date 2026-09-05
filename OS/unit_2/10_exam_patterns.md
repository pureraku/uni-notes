# 10 — Exam Patterns / One-Page Recall

## Critical section

```c
lock();

/* CRITICAL SECTION */

unlock();
```

## Peterson

```c
flag[i] = true;
turn = j;

while (flag[j] && turn == j)
    ;

/* CRITICAL SECTION */

flag[i] = false;
```

## Test-and-set

```c
while (test_and_set(&lock))
    ;
```

## Swap

```c
key = true;

while (key)
    swap(&lock, &key);
```

## Mutex

```c
pthread_mutex_lock(&lock);

/* CRITICAL SECTION */

pthread_mutex_unlock(&lock);
```

## Semaphore

```c
sem_wait(&S);

/* CRITICAL SECTION */

sem_post(&S);
```

## Producer

```c
wait(empty);
wait(mutex);

/* add item */

signal(mutex);
signal(full);
```

## Consumer

```c
wait(full);
wait(mutex);

/* remove item */

signal(mutex);
signal(empty);
```

## Dining philosophers

```c
wait(left);
wait(right);

/* EAT */

signal(left);
signal(right);
```

## Readers–writers

```c
readcount++;

if (readcount == 1)
    wait(rw_mutex);

/* READ */

readcount--;

if (readcount == 0)
    signal(rw_mutex);
```

Writer:

```c
wait(rw_mutex);

/* WRITE */

signal(rw_mutex);
```

## Monitor

```c
pthread_mutex_lock(&mutex);

while (!condition)
    pthread_cond_wait(&cond, &mutex);

/* operation */

pthread_cond_signal(&cond);
pthread_mutex_unlock(&mutex);
```

## Fast numerical/tracing rules

```text
wait(S)   → S--
signal(S) → S++

Producer-consumer:
full + empty = buffer size

Readers-writers:
readcount 0 → 1 = first reader blocks writer
readcount 1 → 0 = last reader allows writer

Process states:
NEW → READY → RUNNING → TERMINATED
RUNNING → WAITING → READY
RUNNING → READY       (preemption)
```

**Memory hook:**

```text
1 lock       → mutex
N permits    → counting semaphore
2 processes  → Peterson
atomic lock  → test-and-set / swap
buffer       → empty + full + mutex
readers      → first/last reader logic
philosophers → multiple resources / deadlock
monitor      → mutex + conditions packaged together
```
