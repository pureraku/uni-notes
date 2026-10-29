/* Experiment 13: Disk Scheduling */
#include <stdio.h>
#include <stdlib.h>

#define REQUEST_COUNT 8
#define LAST_TRACK 199

static const int requests[REQUEST_COUNT] = {95, 180, 34, 119, 11, 123, 62, 64};

static void fcfs(void)
{
    int head = 50;
    int movement = 0;
    printf("FCFS seek sequence: %d", head);
    for (int i = 0; i < REQUEST_COUNT; ++i) {
        movement += abs(requests[i] - head);
        head = requests[i];
        printf(" -> %d", head);
    }
    printf("\nTotal head movement: %d tracks\n", movement);
}

static void scan(void)
{
    int sorted[REQUEST_COUNT];
    for (int i = 0; i < REQUEST_COUNT; ++i)
        sorted[i] = requests[i];
    for (int i = 0; i < REQUEST_COUNT - 1; ++i) {
        for (int j = 0; j < REQUEST_COUNT - i - 1; ++j) {
            if (sorted[j] > sorted[j + 1]) {
                int temporary = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temporary;
            }
        }
    }

    int head = 50;
    int movement = 0;
    printf("SCAN seek sequence (toward higher tracks): %d", head);
    for (int i = 0; i < REQUEST_COUNT; ++i) {
        if (sorted[i] >= head) {
            movement += abs(sorted[i] - head);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }
    movement += LAST_TRACK - head;
    head = LAST_TRACK;
    printf(" -> %d", head);
    for (int i = REQUEST_COUNT - 1; i >= 0; --i) {
        if (sorted[i] < 50) {
            movement += abs(sorted[i] - head);
            head = sorted[i];
            printf(" -> %d", head);
        }
    }
    printf("\nTotal head movement: %d tracks\n", movement);
}

int main(void)
{
    puts("Request queue: 95 180 34 119 11 123 62 64; initial head: 50; tracks: 0-199\n");
    fcfs();
    scan();
    return 0;
}
