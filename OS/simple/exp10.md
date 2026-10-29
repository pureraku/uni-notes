# Experiment 10: FIFO Page Replacement

## Aim
Simulate FIFO page replacement with three frames.

## Compile and run
`cc -std=c11 exp10.c -o exp10 && ./exp10`

For each page in the sample reference string, the program displays the frame contents and whether the access was a hit or fault. On a fault, FIFO replaces the page loaded earliest.
