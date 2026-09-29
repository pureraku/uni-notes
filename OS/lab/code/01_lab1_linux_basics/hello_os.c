#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Hello, Operating Systems Lab!\n");
    printf("Current process PID: %d\n", (int)getpid());

    return 0;
}
