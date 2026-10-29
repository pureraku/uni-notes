/* Experiment 11: LRU and LFU Page Replacement */
#include <stdio.h>

#define PAGE_COUNT 15
#define FRAME_COUNT 3

static const int pages[PAGE_COUNT] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3};

static void print_frames(const int frames[FRAME_COUNT])
{
    for (int i = 0; i < FRAME_COUNT; ++i) {
        if (frames[i] == -1)
            printf("-\t");
        else
            printf("%d\t", frames[i]);
    }
}

static void simulate(int use_lfu)
{
    int frames[FRAME_COUNT] = {-1, -1, -1};
    int last_used[FRAME_COUNT] = {0};
    int frequency[FRAME_COUNT] = {0};
    int faults = 0;

    puts("Page\tFrame 1\tFrame 2\tFrame 3\tResult");
    for (int i = 0; i < PAGE_COUNT; ++i) {
        int hit = -1;
        for (int f = 0; f < FRAME_COUNT; ++f)
            if (frames[f] == pages[i])
                hit = f;

        if (hit >= 0) {
            last_used[hit] = i;
            ++frequency[hit];
        } else {
            ++faults;
            int victim = -1;
            for (int f = 0; f < FRAME_COUNT; ++f) {
                if (frames[f] == -1) {
                    victim = f;
                    break;
                }
            }
            if (victim == -1) {
                victim = 0;
                for (int f = 1; f < FRAME_COUNT; ++f) {
                    int better = use_lfu
                        ? frequency[f] < frequency[victim] ||
                          (frequency[f] == frequency[victim] &&
                           last_used[f] < last_used[victim])
                        : last_used[f] < last_used[victim];
                    if (better)
                        victim = f;
                }
            }
            frames[victim] = pages[i];
            last_used[victim] = i;
            frequency[victim] = 1;
        }

        printf("%d\t", pages[i]);
        print_frames(frames);
        puts(hit >= 0 ? "Hit" : "Fault");
    }
    printf("Total page faults: %d\n", faults);
}

int main(void)
{
    puts("LRU page replacement");
    simulate(0);
    puts("\nLFU page replacement (ties use least recently used)");
    simulate(1);
    return 0;
}
