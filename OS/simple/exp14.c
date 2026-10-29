/* Experiment 14: Sequential and Indexed File Allocation */
#include <stdio.h>

#define DISK_BLOCKS 50
#define FILE_COUNT 4
#define INDEXED_FILES 3
#define BLOCKS_PER_FILE 4

static void sequential_allocation(void)
{
    int used[DISK_BLOCKS] = {0};
    const int start[FILE_COUNT] = {5, 8, 20, 2};
    const int length[FILE_COUNT] = {3, 4, 5, 4};

    puts("Sequential file allocation");
    for (int file = 0; file < FILE_COUNT; ++file) {
        int valid = start[file] >= 0 && start[file] + length[file] <= DISK_BLOCKS;
        for (int block = start[file]; valid && block < start[file] + length[file]; ++block)
            if (used[block])
                valid = 0;
        if (!valid) {
            printf("File %d was not allocated (invalid or occupied block).\n", file + 1);
            continue;
        }
        printf("File %d allocated blocks:", file + 1);
        for (int block = start[file]; block < start[file] + length[file]; ++block) {
            used[block] = 1;
            printf(" %d", block);
        }
        putchar('\n');
    }
}

static void indexed_allocation(void)
{
    int used[DISK_BLOCKS] = {0};
    const int index_block[INDEXED_FILES] = {9, 20, 9};
    const int data_blocks[INDEXED_FILES][BLOCKS_PER_FILE] = {
        {1, 2, 3, 4}, {10, 11, 12, 13}, {30, 31, 32, 33}
    };

    puts("\nIndexed file allocation");
    for (int file = 0; file < INDEXED_FILES; ++file) {
        int index = index_block[file];
        int valid = index >= 0 && index < DISK_BLOCKS && !used[index];
        for (int i = 0; valid && i < BLOCKS_PER_FILE; ++i) {
            int block = data_blocks[file][i];
            if (block < 0 || block >= DISK_BLOCKS || used[block] || block == index)
                valid = 0;
            for (int j = 0; j < i; ++j)
                if (data_blocks[file][j] == block)
                    valid = 0;
        }
        if (!valid) {
            printf("File %d was not allocated (an index or data block is in use).\n", file + 1);
            continue;
        }
        used[index] = 1;
        printf("File %d, index block %d ->", file + 1, index);
        for (int i = 0; i < BLOCKS_PER_FILE; ++i) {
            used[data_blocks[file][i]] = 1;
            printf(" %d", data_blocks[file][i]);
        }
        putchar('\n');
    }
}

int main(void)
{
    sequential_allocation();
    indexed_allocation();
    return 0;
}
