# Experiment 6: Dining Philosophers Problem

## Aim
Simulate five philosophers sharing five forks.

## Compile and run
`cc -pthread exp06.c -o exp06 && ./exp06`

Each fork is a binary semaphore. A room semaphore allows only four philosophers to compete for forks at once, preventing deadlock. Each philosopher thinks and eats once.
