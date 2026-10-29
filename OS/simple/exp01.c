/* Experiment 1: Linux Basics */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int choice;
    const char *commands[] = {
        "echo SRM", "date", "pwd", "ls -la", "cal 2022",
        "wc -l /etc/passwd", "head -5 /etc/passwd", "tail -5 /etc/passwd"
    };
    const char *labels[] = {
        "Display text", "Show date and time", "Show current directory",
        "List files (including hidden files)", "Show calendar for 2022",
        "Count lines in a file", "Show first five lines of a file",
        "Show last five lines of a file"
    };
    size_t count = sizeof commands / sizeof commands[0];

    puts("Basic Linux commands (read-only examples)");
    for (size_t i = 0; i < count; ++i)
        printf("%zu. %s\n", i + 1, labels[i]);
    printf("Choose a command (1-%zu, 0 to quit): ", count);
    if (scanf("%d", &choice) != 1 || choice < 0 || (size_t)choice > count) {
        fputs("Invalid choice.\n", stderr);
        return 1;
    }
    if (choice == 0)
        return 0;
    printf("$ %s\n", commands[choice - 1]);
    if (system(commands[choice - 1]) == -1) {
        perror("Could not run the command");
        return 1;
    }
    puts("\nOperating system installation uses the platform installer.");
    return 0;
}
