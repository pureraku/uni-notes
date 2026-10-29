/* Experiment 10: FIFO Page Replacement */
#include <stdio.h>

#define PAGE_COUNT 14
#define FRAME_COUNT 3

int main(void)
{
    const int pages[PAGE_COUNT] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1};
    int frames[FRAME_COUNT] = {-1, -1, -1};
    int next_frame = 0;
    int faults = 0;

    puts("Page\tFrame 1\tFrame 2\tFrame 3\tResult");
    for (int i = 0; i < PAGE_COUNT; ++i) {
        int hit = 0;
        for (int f = 0; f < FRAME_COUNT; ++f)
            if (frames[f] == pages[i])
                hit = 1;
        if (!hit) {
            frames[next_frame] = pages[i];
            next_frame = (next_frame + 1) % FRAME_COUNT;
            ++faults;
        }
        printf("%d\t", pages[i]);
        for (int f = 0; f < FRAME_COUNT; ++f) {
            if (frames[f] == -1)
                printf("-\t");
            else
                printf("%d\t", frames[f]);
        }
        puts(hit ? "Hit" : "Fault");
    }
    printf("Total page faults: %d\n", faults);
    printf("Total page hits: %d\n", PAGE_COUNT - faults);
    return 0;
}
