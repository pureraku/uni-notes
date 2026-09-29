# Lab 3 — Multithreading

Compile:

```bash
gcc pthread_basic.c -o pthread_basic -pthread
./pthread_basic
```

The program creates multiple threads, passes each an integer argument, and waits for all threads using `pthread_join()`.
