#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        /* Child process */
        printf("Child:\n");
        printf("  PID  = %d\n", (int)getpid());
        printf("  PPID = %d\n", (int)getppid());
    } else {
        /* Parent process */
        printf("Parent:\n");
        printf("  PID      = %d\n", (int)getpid());
        printf("  Child PID = %d\n", (int)pid);

        /*
         * Wait for the child so the parent does not finish
         * before the child terminates.
         */
        if (wait(NULL) == -1) {
            perror("wait failed");
            return EXIT_FAILURE;
        }

        printf("Parent: child has terminated.\n");
    }

    return EXIT_SUCCESS;
}
