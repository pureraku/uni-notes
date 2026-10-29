/* Experiment 2: Process Creation */
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t child = fork();
    if (child == -1) {
        perror("fork");
        return 1;
    }
    if (child == 0) {
        printf("Child process: PID=%ld, parent PID=%ld\n",
               (long)getpid(), (long)getppid());
        return 0;
    }

    printf("Parent process: PID=%ld, child PID=%ld\n",
           (long)getpid(), (long)child);
    int status;
    if (waitpid(child, &status, 0) == -1) {
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status))
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    return 0;
}
