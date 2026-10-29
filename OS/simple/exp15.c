/* Experiment 15: Single-Level and Two-Level Directories */
#include <stdio.h>
#include <string.h>

#define MAX_FILES 10
#define NAME_SIZE 20
#define USER_COUNT 3

typedef struct {
    char name[NAME_SIZE];
    char files[MAX_FILES][NAME_SIZE];
    int count;
} Directory;

static int find_file(const Directory *directory, const char *name)
{
    for (int i = 0; i < directory->count; ++i)
        if (strcmp(directory->files[i], name) == 0)
            return i;
    return -1;
}

static void create_file(Directory *directory, const char *name)
{
    if (find_file(directory, name) >= 0) {
        printf("%s: %s already exists\n", directory->name, name);
    } else if (directory->count == MAX_FILES) {
        printf("%s: directory is full\n", directory->name);
    } else {
        snprintf(directory->files[directory->count], NAME_SIZE, "%s", name);
        ++directory->count;
        printf("%s: created %s\n", directory->name, name);
    }
}

static void delete_file(Directory *directory, const char *name)
{
    int position = find_file(directory, name);
    if (position < 0) {
        printf("%s: %s not found\n", directory->name, name);
        return;
    }
    for (int i = position; i < directory->count - 1; ++i)
        strcpy(directory->files[i], directory->files[i + 1]);
    --directory->count;
    printf("%s: deleted %s\n", directory->name, name);
}

static void list_directory(const Directory *directory)
{
    printf("%s:", directory->name);
    if (directory->count == 0)
        printf(" (empty)");
    for (int i = 0; i < directory->count; ++i)
        printf(" %s", directory->files[i]);
    putchar('\n');
}

int main(void)
{
    Directory single = {"single-level", {{0}}, 0};
    Directory users[USER_COUNT] = {
        {"user1", {{0}}, 0}, {"user2", {{0}}, 0}, {"user3", {{0}}, 0}
    };

    puts("Single-level directory");
    create_file(&single, "notes.txt");
    create_file(&single, "prog.c");
    create_file(&single, "prog.c");
    printf("Search memo.txt: %s\n", find_file(&single, "memo.txt") >= 0 ? "found" : "not found");
    delete_file(&single, "prog.c");
    list_directory(&single);

    puts("\nTwo-level directory");
    create_file(&users[0], "a.txt");
    create_file(&users[0], "b.c");
    create_file(&users[1], "a.txt");
    create_file(&users[1], "b.c");
    create_file(&users[2], "a.txt");
    printf("Search user2/a.txt: %s\n", find_file(&users[1], "a.txt") >= 0 ? "found" : "not found");
    delete_file(&users[0], "b.c");
    for (int i = 0; i < USER_COUNT; ++i)
        list_directory(&users[i]);
    return 0;
}
