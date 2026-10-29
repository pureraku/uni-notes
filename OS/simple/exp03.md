# Experiment 3: Multithreading

## Aim
Create threads and protect a shared counter with a mutex.

## Compile and run
`cc -pthread exp03.c -o exp03 && ./exp03`

Three threads each add 1,000 to the same counter. The final value should be 3,000.
