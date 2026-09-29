#include <stdio.h>

#define MAX 50

typedef struct {
    int pid;
    int at;
    int bt;
    int remaining;
    int priority;
    int ct;
    int tat;
    int wt;
    int done;
} Process;

void print_results(Process p[], int n)
{
    double avg_tat = 0.0;
    double avg_wt = 0.0;

    printf("\nPID\tAT\tBT\tPr\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].ct, p[i].tat, p[i].wt);

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    printf("Average TAT = %.2f\n", avg_tat / n);
    printf("Average WT  = %.2f\n", avg_wt / n);
}

/*
 * Non-preemptive priority scheduling.
 * Assumption: smaller numeric value means higher priority.
 */
void priority_scheduling(Process original[], int n)
{
    Process p[MAX];

    for (int i = 0; i < n; i++) {
        p[i] = original[i];
        p[i].done = 0;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    int completed = 0;
    int time = 0;

    printf("\nPriority Gantt chart:\n");

    while (completed < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (selected == -1 ||
                    p[i].priority < p[selected].priority ||
                    (p[i].priority == p[selected].priority &&
                     p[i].at < p[selected].at) ||
                    (p[i].priority == p[selected].priority &&
                     p[i].at == p[selected].at &&
                     p[i].pid < p[selected].pid)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!p[i].done &&
                    (next == -1 || p[i].at < p[next].at)) {
                    next = i;
                }
            }

            time = p[next].at;
            continue;
        }

        printf("| P%d ", p[selected].pid);

        time += p[selected].bt;
        p[selected].ct = time;
        p[selected].tat = p[selected].ct - p[selected].at;
        p[selected].wt = p[selected].tat - p[selected].bt;
        p[selected].done = 1;
        completed++;
    }

    printf("|\n");

    print_results(p, n);
}

/*
 * Round Robin with arrival times.
 * Smaller process ID breaks otherwise equivalent queue-arrival ties.
 */
void round_robin(Process original[], int n, int quantum)
{
    Process p[MAX];
    int queue[MAX * 10];
    int front = 0;
    int rear = 0;

    for (int i = 0; i < n; i++) {
        p[i] = original[i];
        p[i].remaining = p[i].bt;
        p[i].ct = p[i].tat = p[i].wt = 0;
    }

    int added[MAX] = {0};
    int completed = 0;
    int time = 0;

    printf("\nRound Robin Gantt chart:\n");

    while (completed < n) {
        /*
         * If queue is empty, jump to the next process arrival.
         */
        if (front == rear) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!added[i] &&
                    (next == -1 || p[i].at < p[next].at)) {
                    next = i;
                }
            }

            if (next == -1) {
                break;
            }

            if (time < p[next].at) {
                time = p[next].at;
            }
        }

        /* Add every process that has arrived by current time. */
        for (int i = 0; i < n; i++) {
            if (!added[i] && p[i].at <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (front == rear) {
            continue;
        }

        int current = queue[front++];

        int slice = p[current].remaining < quantum
                    ? p[current].remaining
                    : quantum;

        printf("| P%d ", p[current].pid);

        p[current].remaining -= slice;
        time += slice;

        /* Add processes that arrived during this time slice. */
        for (int i = 0; i < n; i++) {
            if (!added[i] && p[i].at <= time) {
                queue[rear++] = i;
                added[i] = 1;
            }
        }

        if (p[current].remaining > 0) {
            queue[rear++] = current;
        } else {
            p[current].ct = time;
            p[current].tat = p[current].ct - p[current].at;
            p[current].wt = p[current].tat - p[current].bt;
            completed++;
        }
    }

    printf("|\n");

    print_results(p, n);
}

int main(void)
{
    Process p[MAX];
    int n;
    int quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter AT, BT and Priority for P%d: ", p[i].pid);
        scanf("%d %d %d",
              &p[i].at,
              &p[i].bt,
              &p[i].priority);

        if (p[i].at < 0 || p[i].bt <= 0) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Quantum must be positive.\n");
        return 1;
    }

    priority_scheduling(p, n);
    round_robin(p, n, quantum);

    return 0;
}
