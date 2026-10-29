# Experiment 9: Priority and Round Robin scheduling

## Aim
Demonstrate non-preemptive priority scheduling and Round Robin scheduling.

## Compile and run
`cc -std=c11 exp09.c -o exp09 && ./exp09`

All sample processes arrive at time zero. A smaller priority number means higher priority. Round Robin uses a time quantum of 3 and calculates completion, waiting, and turnaround times.
