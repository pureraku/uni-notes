# Experiment 2: Process creation

## Aim
Create a child process with `fork()` and use `getpid()`, `getppid()`, and `waitpid()`.

## Compile and run
`cc -std=c11 exp02.c -o exp02 && ./exp02`

The child prints its PID and parent PID. The parent prints both process IDs and waits for the child, preventing a zombie process.
