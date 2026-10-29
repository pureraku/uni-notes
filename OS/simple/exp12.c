/* Experiment 12: Best Fit and Worst Fit Memory Management */
#include <stdio.h>

#define BLOCK_COUNT 5
#define PROCESS_COUNT 4

static void allocate(const char *title, int best_fit)
{
    int blocks[BLOCK_COUNT] = {100, 50, 30, 120, 35};
    int processes[PROCESS_COUNT] = {40, 10, 30, 60};
    int allocated[BLOCK_COUNT] = {0};

    printf("\n%s\n", title);
    puts("Process  Size  Block");
    for (int p = 0; p < PROCESS_COUNT; ++p) {
        int selected = -1;
        for (int b = 0; b < BLOCK_COUNT; ++b) {
            if (allocated[b] || blocks[b] < processes[p])
                continue;
            if (selected == -1 ||
                (best_fit && blocks[b] < blocks[selected]) ||
                (!best_fit && blocks[b] > blocks[selected]))
                selected = b;
        }
        if (selected == -1) {
            printf("P%d       %4d  Not allocated\n", p + 1, processes[p]);
        } else {
            allocated[selected] = 1;
            printf("P%d       %4d  Block %d (%d units)\n", p + 1,
                   processes[p], selected + 1, blocks[selected]);
        }
    }
}

int main(void)
{
    allocate("Best Fit", 1);
    allocate("Worst Fit", 0);
    return 0;
}
