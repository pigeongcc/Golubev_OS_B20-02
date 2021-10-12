#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/resource.h>

#define TEN_MB 10 * 1024 * 1024
#define HUNDRED_MB 100 * 1024 * 1024
#define FIVE_HUNDRED_MB 500 * 1024 * 1024

int main() {
    int memSize = HUNDRED_MB;
    struct rusage * rusagePtr = malloc(sizeof(struct rusage));

    printf("stime\t\tmaxrss\t\tixrss\tidrss\tisrss\n");
    int i =0;
    while(i < 10) {
        void* memPtr = malloc(memSize);
        memset(memPtr, 0, memSize);

        getrusage(RUSAGE_SELF, rusagePtr);

        struct timeval stime = rusagePtr->ru_stime;
        time_t stime_sec = stime.tv_sec;
        suseconds_t stime_usec = stime.tv_usec;

        printf("%ld.%ld\t", stime_sec, stime_usec);
        printf("%ld\t\t", rusagePtr->ru_maxrss);
        printf("%ld\t\t", rusagePtr->ru_ixrss);
        printf("%ld\t\t", rusagePtr->ru_idrss);
        printf("%ld\n", rusagePtr->ru_isrss);

        i++;
        sleep(1);
    }

    printf("%d MB of memory has been allocated.\n", memSize/(1024*1024));

    return 0;
}