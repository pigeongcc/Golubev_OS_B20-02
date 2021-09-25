#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Process {
    int arrival, burst, burstLeft, completion, turnaround, waiting, index;
    bool isCompleted;
};

void swapProcesses(struct Process* a, struct Process* b) {
    struct Process c;
    c = *a;
    *a = *b;
    *b = c;
}

// while not

int main() {
    int quantum, n;
    printf("Enter the integer duraion of quantum: ");
    scanf("%d", &quantum);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process * process = malloc(n * sizeof(struct Process));
    printf("Enter arrival time and burst time for each process:\n");
    for(int i = 0; i < n; i++) {
        printf("Arrival time for process #%d: ", i+1);
        scanf("%d", &(process[i].arrival));

        printf("Burst time for process #%d: ", i+1);
        scanf("%d", &(process[i].burst));
        process[i].burstLeft = process[i].burst;

        process[i].isCompleted = 0;
        process[i].index = i+1;
    }

    // sorting of the processes by arrival time
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (process[j].arrival > process[j+1].arrival)
                swapProcesses(&process[j], &process[j+1]);

    int processesComplete = 0, currentTime = 0;
    while (processesComplete < n) {
        int lastCurrentTime = currentTime;
        for(int i = 0; i < n; i++) {
            if(!process[i].isCompleted && process[i].arrival <= currentTime) {
                if(process[i].burstLeft <= quantum) {
                    currentTime += process[i].burstLeft;
                    process[i].burstLeft = 0;
                    process[i].isCompleted = 1;
                    processesComplete++;

                    process[i].waiting = currentTime - process[i].arrival - process[i].burst;
                    process[i].turnaround = currentTime - process[i].arrival;
                    process[i].completion = currentTime;
                }
                else {
                    process[i].burstLeft -= quantum;
                    currentTime += quantum;
                }
            }
        }
        // if no process used CPU time, then make a time step
        if(currentTime == lastCurrentTime) {
            currentTime++;
        }
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

/*
 ****************** COMPARISON OF METHODS ******************
 * The test is from the lab presentation slide 6 out of 13
 *
 * 1) First come, first served

P#	    AT	    BT	    CT	    TAT	    WT

P1      0       1       1       1       0
P2      0       2       3       3       1
P3      0       4       7       7       3
P4      0       6       13      13      7
P5      0       8       21      21      13
P6      11      8       29      18      10
P7      11      6       35      24      18
P8      11      4       39      28      24
P9      11      2       41      30      28
P10     11      1       42      31      30

Average Turnaround Time = 17.600000
Average Waiting Time = 13.400000

 * 2) Shortest job next

P#	    AT	    BT	    CT	    TAT	    WT

P1      0       1       1       1       0
P2      0       2       3       3       1
P3      0       4       7       7       3
P4      0       6       13      13      7
P5      0       8       34      34      26
P6      11      8       42      31      23
P7      11      6       26      15      9
P8      11      4       20      9       5
P9      11      2       16      5       3
P10     11      1       14      3       2

Average Turnaround Time = 12.100000
Average Waiting Time = 7.900000

 * 3) Round robin (quantum = 3)

P#	    AT	    BT	    CT	    TAT	    WT

P1      0       1       1       1       0
P2      0       2       3       3       1
P3      0       4       25      25      21
P4      0       6       28      28      22
P5      0       8       40      40      32
P6      11      8       42      31      23
P7      11      6       37      26      20
P8      11      4       38      27      23
P9      11      2       23      12      10
P10     11      1       24      13      12

Average Turnaround Time = 20.600000
Average Waiting Time = 16.400000


 * Thus, both the shortest avg turnaround and avg waiting time for a given example are shown
 * by the "shortest job next" strategy.
 *
 * However, the "shortest job next" strategy requires us to know the burst time of the process beforehand.
 * In real systems, prediction of burst time is quite an expensive operation, and in many cases it's cheaper
 * to run the processes using another strategy, that doesn't require the prediction. For instance, Round-robin
 * or FIFS strategy.
 */