# 01 — Peterson's Solution

For **two processes/threads**.

```text
flag[i] = "I want to enter"
turn    = "let the other go first"
```

## Actual C code

```c
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

atomic_bool flag[2];
atomic_int turn;

int shared = 0;

void enter_region(int i)
{
    int j = 1 - i;

    atomic_store_explicit(&flag[i], true, memory_order_seq_cst);
    atomic_store_explicit(&turn, j, memory_order_seq_cst);

    while (atomic_load_explicit(&flag[j], memory_order_seq_cst) &&
           atomic_load_explicit(&turn, memory_order_seq_cst) == j) {
        /* busy wait */
    }
}

void leave_region(int i)
{
    atomic_store_explicit(&flag[i], false, memory_order_seq_cst);
}

void *worker(void *arg)
{
    int i = *(int *)arg;

    for (int k = 0; k < 100000; k++) {
        enter_region(i);

        /* CRITICAL SECTION */
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
```

Compile:

```bash
gcc 01_petersons_solution.c -pthread -std=c11
```

**One-liner:** `flag` says who wants in; `turn` breaks the tie.

> Exam note: the textbook form is usually written with `boolean flag[2]` and `int turn`; the C version above makes the shared variables atomic so the program is meaningful as real multithreaded C.
