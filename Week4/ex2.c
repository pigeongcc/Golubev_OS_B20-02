#include <unistd.h>

/*
 * The program allows to trace the process hierarchy over time.
 *
 * Calling pstree before the running of the program, every 5 seconds after the start of it, and after the execution
 * allows to see the hierarchy of ex2 processes. ex2 doubles itself every 5 seconds. Each new "layer" of ex2
 * is doubled as well.
 * In the end we'll see 15 (i = 3 case) or 31 (i = 5 case) ex2 processes.
 *
 * In UNIX systems, the described hierarchy is called a process group.
 */

int main() {
    for(int i = 1; i <= 5; i++) {
        fork();
        sleep(5);
    }

    return 0;
}
