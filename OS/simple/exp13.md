# Experiment 13: Disk Scheduling

## Aim
Compare FCFS and SCAN disk scheduling.

## Compile and run
`cc -std=c11 exp13.c -o exp13 && ./exp13`

The request queue is 95, 180, 34, 119, 11, 123, 62, 64. The initial head is track 50, with tracks 0–199. SCAN first moves toward higher tracks, reaches track 199, then reverses.
