/* Value Added Program 2: Debugging C Programs with GDB */
#include <stdio.h>

int main(void)
{
    int sum = 0;
    for (int value = 1; value <= 5; ++value) {
        sum += value;
        printf("After adding %d, sum = %d\n", value, sum);
    }
    printf("Final sum = %d\n", sum);
    return 0;
}
