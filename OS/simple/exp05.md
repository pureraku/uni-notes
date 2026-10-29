# Experiment 5: Reader-Writer Problem

## Aim
Allow multiple readers to share data while ensuring a writer has exclusive access.

## Compile and run
`cc -pthread exp05.c -o exp05 && ./exp05`

A semaphore locks the shared resource for a writer. A mutex protects the reader count; the first reader locks the resource and the last reader releases it.
