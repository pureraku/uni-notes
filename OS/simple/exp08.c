/* Experiment 8: FCFS and SJF Scheduling */
#include <stdio.h>

#define PROCESS_COUNT 4

static void schedule(const char *title, int shortest_job_first)
{
    int burst[PROCESS_COUNT] = {6, 8, 7, 3};
    int order[PROCESS_COUNT] = {0, 1, 2, 3};
    int waiting[PROCESS_COUNT] = {0};
    int turnaround[PROCESS_COUNT];
    int elapsed = 0;
    double total_waiting = 0;
    double total_turnaround = 0;

    if (shortest_job_first) {
        for (int i = 0; i < PROCESS_COUNT - 1; ++i)
            for (int j = i + 1; j < PROCESS_COUNT; ++j)
                if (burst[order[j]] < burst[order[i]]) {
                    int temporary = order[i];
                    order[i] = order[j];
                    order[j] = temporary;
                }
    }
    printf("\n%s\n", title);
    puts("Process  Burst  Waiting  Turnaround");
    for (int i = 0; i < PROCESS_COUNT; ++i) {
        int p = order[i];
        waiting[p] = elapsed;
        turnaround[p] = waiting[p] + burst[p];
        elapsed += burst[p];
        total_waiting += waiting[p];
        total_turnaround += turnaround[p];
        printf("P%d       %5d  %7d  %10d\n", p + 1, burst[p], waiting[p],
               turnaround[p]);
    }
    printf("Average waiting time: %.2f\n", total_waiting / PROCESS_COUNT);
    printf("Average turnaround time: %.2f\n",
           total_turnaround / PROCESS_COUNT);
}

int main(void)
{
    schedule("FCFS", 0);
    schedule("SJF (non-preemptive)", 1);
    return 0;
}
