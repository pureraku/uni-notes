#include <stdio.h>

#define MAX 50

typedef struct {
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int done;
} Process;

void reset(Process p[], int n)
{
    for (int i = 0; i < n; i++) {
        p[i].ct = 0;
        p[i].tat = 0;
        p[i].wt = 0;
        p[i].done = 0;
    }
}

void print_results(Process p[], int n)
{
    double avg_tat = 0.0;
    double avg_wt = 0.0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);

        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }

    printf("Average TAT = %.2f\n", avg_tat / n);
    printf("Average WT  = %.2f\n", avg_wt / n);
}

/* FCFS: sort by arrival time, then execute in that order. */
void fcfs(Process original[], int n)
{
    Process p[MAX];

    for (int i = 0; i < n; i++) {
        p[i] = original[i];
    }

    reset(p, n);

    /* Simple stable-ish bubble sort by arrival time and PID. */
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at ||
                (p[j].at == p[j + 1].at && p[j].pid > p[j + 1].pid)) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }

    int time = 0;

    printf("\nFCFS Gantt chart:\n");

    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at;
        }

        printf("| P%d ", p[i].pid);
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }

    printf("|\n");

    print_results(p, n);
}

/* Non-preemptive SJF: choose the shortest burst among ready processes. */
void sjf(Process p[], int n)
{
    Process a[MAX];

    for (int i = 0; i < n; i++) {
        a[i] = p[i];
    }

    reset(a, n);

    int completed = 0;
    int time = 0;

    printf("\nNon-preemptive SJF Gantt chart:\n");

    while (completed < n) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (!a[i].done && a[i].at <= time) {
                if (selected == -1 ||
                    a[i].bt < a[selected].bt ||
                    (a[i].bt == a[selected].bt && a[i].at < a[selected].at) ||
                    (a[i].bt == a[selected].bt && a[i].at == a[selected].at &&
                     a[i].pid < a[selected].pid)) {
                    selected = i;
                }
            }
        }

        if (selected == -1) {
            /* CPU is idle until the next process arrives. */
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (!a[i].done &&
                    (next == -1 || a[i].at < a[next].at)) {
                    next = i;
                }
            }

            time = a[next].at;
            continue;
        }

        printf("| P%d ", a[selected].pid);

        time += a[selected].bt;
        a[selected].ct = time;
        a[selected].tat = a[selected].ct - a[selected].at;
        a[selected].wt = a[selected].tat - a[selected].bt;
        a[selected].done = 1;
        completed++;
    }

    printf("|\n");

    print_results(a, n);
}

int main(void)
{
    Process p[MAX];
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("Enter AT and BT for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);

        if (p[i].at < 0 || p[i].bt <= 0) {
            printf("Invalid AT/BT.\n");
            return 1;
        }
    }

    fcfs(p, n);
    sjf(p, n);

    return 0;
}
