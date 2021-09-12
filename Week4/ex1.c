#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * The program shows the work of the system scheduler.
 *
 * On my machine, I have the groups of child and parent processes printed batch by batch.
 * There are i processes in each batch.
 * Sometimes the intersections happen, when the first child process is ran before the last parent one.
 *
 * We see the order in which the system scheduler switches the processes from 'Ready' state to 'Running'.
 */

int main() {
    pid_t pid;  // process ID
    pid = fork();
    int n = 10;
    for(int i = 1; i <= n; i++) {
        if(pid > 0) // parent
            printf("Hello from parent [%d - %d]\n", pid, i);
        else if(pid == 0)   // child
            printf("Hello from child [%d - %d]\n", pid, i);
        else
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
