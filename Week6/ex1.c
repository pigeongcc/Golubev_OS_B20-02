#include <stdio.h>
#include <stdlib.h>

struct Process {
    int arrival, burst, completion, turnaround, waiting, index;
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

        process[i].index = i+1;
    }

    // sorting by arrival time
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (process[j].arrival > process[j+1].arrival)
                swapProcesses(&process[j], &process[j+1]);

    process[0].waiting = 0;
    process[0].turnaround = process[0].burst;
    process[0].completion = process[0].arrival + process[0].burst;

    for(int i = 1; i < n; i++) {
        if(process[i-1].completion < process[i].arrival)
            process[i].waiting = process[i].arrival;
        else
            process[i].waiting = process[i-1].completion - process[i].arrival;

        process[i].turnaround = process[i].waiting + process[i].burst;

        process[i].completion = process[i].arrival + process[i].turnaround;
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
