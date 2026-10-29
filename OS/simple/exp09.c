/* Experiment 9: Priority and Round Robin Scheduling */
#include <stdio.h>

#define PROCESS_COUNT 4

static void priority_schedule(void)
{
    int burst[PROCESS_COUNT] = {5, 3, 8, 6};
    int priority[PROCESS_COUNT] = {2, 1, 4, 3};
    int done[PROCESS_COUNT] = {0};
    int waiting[PROCESS_COUNT] = {0};
    int elapsed = 0;
    double total_wait = 0;
    puts("Priority scheduling (smaller number means higher priority)");
    puts("Process  Priority  Burst  Waiting  Turnaround");
    for (int k = 0; k < PROCESS_COUNT; ++k) {
        int p = -1;
        for (int i = 0; i < PROCESS_COUNT; ++i)
            if (!done[i] && (p == -1 || priority[i] < priority[p]))
                p = i;
        waiting[p] = elapsed;
        elapsed += burst[p];
        done[p] = 1;
        total_wait += waiting[p];
        printf("P%d       %8d  %5d  %7d  %10d\n", p + 1, priority[p],
               burst[p], waiting[p], waiting[p] + burst[p]);
    }
    printf("Average waiting time: %.2f\n", total_wait / PROCESS_COUNT);
}

static void round_robin(void)
{
    int burst[PROCESS_COUNT] = {5, 3, 8, 6};
    int remaining[PROCESS_COUNT];
    int completion[PROCESS_COUNT] = {0};
    const int quantum = 3;
    int time = 0;
    int unfinished = PROCESS_COUNT;
    double total_wait = 0;
    for (int i = 0; i < PROCESS_COUNT; ++i)
        remaining[i] = burst[i];

    puts("\nRound Robin (time quantum = 3)");
    while (unfinished > 0) {
        int made_progress = 0;
        for (int p = 0; p < PROCESS_COUNT; ++p) {
            if (remaining[p] == 0)
                continue;
            int slice = remaining[p] < quantum ? remaining[p] : quantum;
            printf("P%d runs from %d to %d\n", p + 1, time, time + slice);
            time += slice;
            remaining[p] -= slice;
            made_progress = 1;
            if (remaining[p] == 0) {
                completion[p] = time;
                --unfinished;
            }
        }
        if (!made_progress)
            break;
    }
    puts("Process  Burst  Waiting  Turnaround");
    for (int p = 0; p < PROCESS_COUNT; ++p) {
        int turnaround = completion[p];
        int waiting = turnaround - burst[p];
        total_wait += waiting;
        printf("P%d       %5d  %7d  %10d\n", p + 1, burst[p], waiting,
               turnaround);
    }
    printf("Average waiting time: %.2f\n", total_wait / PROCESS_COUNT);
}

int main(void)
{
    priority_schedule();
    round_robin();
    return 0;
}
