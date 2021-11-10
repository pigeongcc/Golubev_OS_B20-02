#include <stdio.h>

#define INPUT_FILENAME "C:\\Users\\gulya\\Desktop\\OS\\Golubev_OS_B20-02\\Week13\\input_dl.txt"
#define NUM_OF_PROCESSES 5
#define NUM_OF_RESOURCES_CLASSES 3

int main(void) {

    // Existing resources instances
    int res_exist[NUM_OF_RESOURCES_CLASSES];
    // Available resources instances
    int res_available[NUM_OF_RESOURCES_CLASSES];
    // Current allocation matrix
    int cur_alloc[NUM_OF_PROCESSES][NUM_OF_RESOURCES_CLASSES];
    // Requests matrix
    int request[NUM_OF_PROCESSES][NUM_OF_RESOURCES_CLASSES];

    // reading the input
    FILE *fp;
    fp = fopen(INPUT_FILENAME, "r");

    for(int i = 0; i < NUM_OF_RESOURCES_CLASSES; i++)
        fscanf(fp, "%d", &res_exist[i]);

    for(int i = 0; i < NUM_OF_RESOURCES_CLASSES; i++)
        fscanf(fp, "%d", &res_available[i]);

    for(int i = 0; i < NUM_OF_PROCESSES; i++)
        for(int j = 0; j < NUM_OF_RESOURCES_CLASSES; j ++)
            fscanf(fp, "%d", &cur_alloc[i][j]);

    for(int i = 0; i < NUM_OF_PROCESSES; i++)
        for(int j = 0; j < NUM_OF_RESOURCES_CLASSES; j ++)
            fscanf(fp, "%d", &request[i][j]);

    fclose(fp);

    // banker's algorithm
    int finished[NUM_OF_PROCESSES];
    for (int i  = 0; i < NUM_OF_PROCESSES; i++)
        finished[i] = 0;
    int chain[NUM_OF_PROCESSES];
    int index_chained = 0;

    for (int k = 0; k < NUM_OF_PROCESSES; k++) {
        for (int i = 0; i < NUM_OF_PROCESSES; i++) {
            // if the process is not yet finished
            if (finished[i] == 0) {
                int terminated = 1;
                // check if it's impossible for a process to terminate
                for (int j = 0; j < NUM_OF_RESOURCES_CLASSES; j++) {
                    if (request[i][j] > res_available[j]){
                        terminated = 0;
                        break;
                    }
                }

                // if yes, add the process to the list
                if (terminated == 1) {
                    chain[index_chained++] = i;
                    for (int y = 0; y < NUM_OF_RESOURCES_CLASSES; y++)
                        res_available[y] += cur_alloc[i][y];
                    finished[i] = 1;
                }
            }
        }
    }

    // if all the processes have terminated
    if (index_chained == NUM_OF_PROCESSES)
        printf("There is NO deadlock.\n");
    // otherwise print the number of the process which has been deadlocked
    else {
        int dl_process = chain[index_chained-1];
        printf("There is a deadlock: process %d", dl_process);
    }

    return 0;
}