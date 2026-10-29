# Experiment 4: Mutual Exclusion Using Semaphore and Monitor

## Aim
Limit access to a shared room and safely update its occupancy.

## Compile and run
`cc -pthread exp04.c -o exp04 && ./exp04`

A counting semaphore allows at most two people into the room. A mutex protects the shared occupancy count, demonstrating monitor-style mutual exclusion.
