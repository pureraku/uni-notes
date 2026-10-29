/* Value Added Program 1: Shell Concepts in C */
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int parse_integer(const char *text, int *value)
{
    char *end;
    errno = 0;
    long parsed = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0' || parsed < INT_MIN || parsed > INT_MAX)
        return 0;
    *value = (int)parsed;
    return 1;
}

int main(int argc, char **argv)
{
    int first;
    int second;
    if (argc != 3 || !parse_integer(argv[1], &first) || !parse_integer(argv[2], &second)) {
        fprintf(stderr, "Usage: %s integer integer\n", argv[0]);
        return 1;
    }

    printf("Variables: first=%d, second=%d\n", first, second);
    printf("Arguments supplied: %d\n", argc - 1);
    printf("Sum: %lld\n", (long long)first + second);
    if (first > second)
        puts("First value is greater");
    else if (first == second)
        puts("Values are equal");
    else
        puts("Second value is greater");

    switch (second) {
    case 1:
        puts("Second value is one");
        break;
    case 5:
        puts("Second value is five");
        break;
    default:
        puts("Second value is something else");
    }

    for (int i = 1; i <= 3; ++i)
        printf("for loop: %d\n", i);
    int i = 1;
    while (i <= 3) {
        printf("while loop: %d\n", i);
        ++i;
    }
    return 0;
}
