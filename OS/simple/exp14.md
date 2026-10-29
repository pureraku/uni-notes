# Experiment 14: File Allocation

## Aim
Simulate sequential and indexed file allocation on a disk of 50 blocks.

## Compile and run
`cc -std=c11 exp14.c -o exp14 && ./exp14`

Sequential allocation checks that every block in a requested range is free before reserving any of them. Indexed allocation reserves an index block and all listed data blocks only when the complete set is available.
