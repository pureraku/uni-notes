# Experiment 7: Banker’s Algorithm

## Aim
Use Banker’s safety algorithm to determine whether the sample allocation is safe.

## Compile and run
`cc -std=c11 exp07.c -o exp07 && ./exp07`

The program calculates the Need matrix from Maximum minus Allocation, then repeatedly finds a process whose remaining need fits the available resources. It reports a safe execution sequence or an unsafe state.
