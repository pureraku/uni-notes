# Lab 7 — Banker's Algorithm

`bankers_algorithm.c`:
- reads Allocation, Max, and Available
- calculates Need
- performs the safety algorithm
- prints a safe sequence if one exists

Compile:

```bash
gcc bankers_algorithm.c -o bankers
./bankers
```

Input format:

```text
Number of processes: 5
Number of resource types: 3
Allocation matrix
Max matrix
Available vector
```
