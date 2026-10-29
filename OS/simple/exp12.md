# Experiment 12: Best Fit and Worst Fit

## Aim
Assign processes to fixed memory blocks using Best Fit and Worst Fit.

## Compile and run
`cc -std=c11 exp12.c -o exp12 && ./exp12`

Each block is assigned to at most one process. Best Fit selects the smallest adequate free block; Worst Fit selects the largest adequate free block. The sample block and process sizes are defined near the start of the source.
