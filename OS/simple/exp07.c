/* Experiment 7: Banker’s Algorithm */
#include <stdio.h>

#define PROCESSES 5
#define RESOURCES 3

int main(void)
{
    int allocation[PROCESSES][RESOURCES] = {
        {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}
    };
    int maximum[PROCESSES][RESOURCES] = {
        {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}
    };
    int available[RESOURCES] = {3, 3, 2};
    int need[PROCESSES][RESOURCES];
    int finished[PROCESSES] = {0};
    int sequence[PROCESSES];
    int count = 0;

    for (int p = 0; p < PROCESSES; ++p) {
        for (int r = 0; r < RESOURCES; ++r) {
            if (maximum[p][r] < allocation[p][r]) {
                fprintf(stderr, "Invalid input: allocation exceeds maximum.\n");
                return 1;
            }
            need[p][r] = maximum[p][r] - allocation[p][r];
        }
    }
    puts("Need matrix (A B C):");
    for (int p = 0; p < PROCESSES; ++p)
        printf("P%d: %d %d %d\n", p, need[p][0], need[p][1], need[p][2]);

    while (count < PROCESSES) {
        int progress = 0;
        for (int p = 0; p < PROCESSES; ++p) {
            if (finished[p])
                continue;
            int can_finish = 1;
            for (int r = 0; r < RESOURCES; ++r)
                if (need[p][r] > available[r])
                    can_finish = 0;
            if (can_finish) {
                for (int r = 0; r < RESOURCES; ++r)
                    available[r] += allocation[p][r];
                finished[p] = 1;
                sequence[count++] = p;
                progress = 1;
            }
        }
        if (!progress)
            break;
    }
    if (count != PROCESSES) {
        puts("The system is in an unsafe state.");
        return 0;
    }
    printf("Safe sequence: ");
    for (int i = 0; i < PROCESSES; ++i)
        printf("P%d%s", sequence[i], i + 1 == PROCESSES ? "\n" : " -> ");
    return 0;
}
