/*
 * ================ ex2 COMMENTS ================
 * This was an exciting experiment on my laptop! It has 6 GB of RAM and quite a slow HDD.
 *
 * After allocating of 100 or 1000 MB in total: 'so' became approx. 255, and
 * 'si' got values ~60 couple of times, which is not big amount of memory.
 *
 * However, after allocating 500 MB each second, 'so' parameter began to take the values of
 * 10k-50k starting from the 4th second. Then the laptop frozen. I suppose there was some period of time when
 * my OS was waiting for some memory to be freed. But after this period nothing changed, and Uduntu decided
 * to kill ex2 process which was depicted in the terminal.
 *
 * What was further is 'si' parameter became to take the values 800-2500, and it continued for a couple of minutes.
 * This means the OS swapped the delayed processes back in RAM to reanimate my poor PC.
 *
 * Now I understand why computers may work slowly: if they run out of main memory, their speed may be limited by swapping speed.
 *
 * ================ ex3 COMMENTS ================
 * After running top -d with ex2 running in the background and allocating 1000 MB, I got ex2 process taking ~9% of CPU time.
 * Its memory load smoothly raised from ~1% to ~17%. VIRT parameter was also increasing to its maximum of ~1,000,000 KB
 * which is approx. 1000 MB.
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>

#define TEN_MB 10 * 1024 * 1024
#define HUNDRED_MB 100 * 1024 * 1024
#define FIVE_HUNDRED_MB 500 * 1024 * 1024

int main() {
    int memSize = HUNDRED_MB;

    int i =0;
    while(i < 10) {
        void* memPtr = malloc(memSize);
        memset(memPtr, 0, memSize);

        i++;
        sleep(1);
    }

    printf("%d MB of memory has been allocated.\n", memSize/(1024*1024));

    return 0;
}