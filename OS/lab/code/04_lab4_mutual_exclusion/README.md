# Lab 4 — Mutual Exclusion

## `semaphore_mutex.c`
Protects a shared counter using a binary semaphore.

Compile:

```bash
gcc semaphore_mutex.c -o semaphore_mutex -pthread
./semaphore_mutex
```

## `monitor_style.c`
Demonstrates the monitor-style idea using a POSIX mutex and condition variable.

Compile:

```bash
gcc monitor_style.c -o monitor_style -pthread
./monitor_style
```

POSIX C does not provide a single primitive named `monitor`; the second program constructs monitor-like behavior using a mutex and condition variable.
