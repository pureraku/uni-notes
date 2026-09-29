#include <stdio.h>
#include <stdbool.h>

#define MAX_P 20
#define MAX_R 10

int main(void)
{
    int n, m;
    int allocation[MAX_P][MAX_R];
    int max[MAX_P][MAX_R];
    int need[MAX_P][MAX_R];
    int available[MAX_R];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    if (n <= 0 || n > MAX_P || m <= 0 || m > MAX_R) {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter Available vector:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &available[j]);
    }

    /* Need = Max - Allocation */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];

            if (need[i][j] < 0) {
                printf("Invalid input: Allocation exceeds Max.\n");
                return 1;
            }
        }
    }

    printf("\nNeed matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int work[MAX_R];
    bool finish[MAX_P] = {false};
    int safe_sequence[MAX_P];
    int count = 0;

    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    /*
     * Find a process whose remaining Need can be satisfied.
     * If it finishes, it returns its Allocation to Work.
     */
    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (finish[i]) {
                continue;
            }

            bool can_finish = true;

            for (int j = 0; j < m; j++) {
                if (need[i][j] > work[j]) {
                    can_finish = false;
                    break;
                }
            }

            if (can_finish) {
                for (int j = 0; j < m; j++) {
                    work[j] += allocation[i][j];
                }

                safe_sequence[count++] = i;
                finish[i] = true;
                found = true;
            }
        }

        if (!found) {
            break;
        }
    }

    if (count == n) {
        printf("\nSystem is in a SAFE state.\n");
        printf("Safe sequence: ");

        for (int i = 0; i < n; i++) {
            printf("P%d", safe_sequence[i]);
            if (i != n - 1) {
                printf(" -> ");
            }
        }

        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE state.\n");
    }

    return 0;
}
