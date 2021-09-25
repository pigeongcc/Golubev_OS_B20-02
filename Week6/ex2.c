#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    int arrival, burst, completion, turnaround, waiting, index;
    bool isCompleted;
};

void swapProcesses(struct Process* a, struct Process* b) {
    struct Process c;
    c = *a;
    *a = *b;
    *b = c;
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process * process = malloc(n * sizeof(struct Process));
    printf("Enter arrival time and burst time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("Arrival time for process #%d: ", i+1);
        scanf("%d", &(process[i].arrival));

        printf("Burst time for process #%d: ", i+1);
        scanf("%d", &(process[i].burst));

        process[i].isCompleted = 0;
        process[i].index = i+1;
    }

    int processesComplete = 0, currentTime = 0;
    while (processesComplete < n) {
        // we sort by burst among waiting processes

        // firstly, detect the processes waiting
        struct Process** processWaiting = malloc(n * sizeof(struct Process *));
        // count denotes the current number of waiting processes
        int count = 0;
        for(int i = 0; i < n; i++)
            if(!process[i].isCompleted && currentTime >= process[i].arrival) {
                // append process to the list of waiting processes
                processWaiting[count] = &process[i];
                //printf("New process (%d,%d) is WAITING\n\n", process[i].arrival, process[i].burst);
                count++;
            }

        // if there are no waiting processors at the moment, then make a time step
        if(count == 0) {
            currentTime++;
            continue;
        }

        // then, sort the waiting processes by their burst time
        for (int i = 0; i < count-1; i++)
            for (int j = 0; j < count-i-1; j++)
                if (processWaiting[j]->burst > processWaiting[j+1]->burst)
                    swapProcesses(processWaiting[j], processWaiting[j+1]);

        // now, execute the first process in the list (it's the process with the shortest burst time)
        struct Process * processExecuted = processWaiting[0];
        /*
        for(int i = 0; i < count - 1; i++)      // ??? just count maybe
            processWaiting[i] = processWaiting[i+1];
        count--;
         */

        // compute the process' metrics
        processExecuted->waiting = currentTime - processExecuted->arrival;
        processExecuted->turnaround = processExecuted->waiting + processExecuted->burst;
        processExecuted->completion = processExecuted->arrival + processExecuted->turnaround;


        // move the currentTime to this process' completion time
        currentTime = processExecuted->completion;

        /*
        printf("New process executed:\n");
        printf("%d\t", processExecuted->arrival);
        printf("%d\t", processExecuted->burst);
        printf("%d\t", processExecuted->completion);
        printf("%d\t", processExecuted->turnaround);
        printf("%d\n", processExecuted->waiting);
        printf("Now the currentTime is %d\n\n", currentTime);
        */

        // this process is considered to be completed
        processExecuted->isCompleted = 1;
        processesComplete++;
    }

    // sorting of the processes by index
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (process[j].index > process[j+1].index)
                swapProcesses(&process[j], &process[j+1]);

    int turnaroundSum = 0, waitingSum = 0;
    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t", i+1);
        printf("%d\t", process[i].arrival);
        printf("%d\t", process[i].burst);
        printf("%d\t", process[i].completion);
        printf("%d\t", process[i].turnaround);
        printf("%d\n", process[i].waiting);

        turnaroundSum += process[i].turnaround;
        waitingSum += process[i].waiting;
    }

    double turnaroundAvg = (double)turnaroundSum / n;
    double waitingAvg = (double)waitingSum / n;

    printf("\n");
    printf("Average Turnaround Time = %f\n", turnaroundAvg);
    printf("Average Waiting Time = %f\n", waitingAvg);

    return 0;
}
