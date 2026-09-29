# Lab 6 — Dining Philosophers

`dining_philosophers.c` uses an arbitrator semaphore allowing at most four philosophers to compete for five forks. This breaks the simple all-five-hold-one-fork circular deadlock scenario.

Compile:

```bash
gcc dining_philosophers.c -o dining_philosophers -pthread
./dining_philosophers
```

The program demonstrates deadlock avoidance, not a proof of every possible fairness property.
