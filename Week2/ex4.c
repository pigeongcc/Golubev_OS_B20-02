#include <stdio.h>
#include "stdbool.h"
#include "stdlib.h"
#include "string.h"
#define BUFFER_SIZE 1000

void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

bool isInteger(char* line) {
    int startIndex = 0;

    // for negative numbers
    if(line[0] == '-' && strlen(line) > 1 && line[1] > '0')
        startIndex = 1;

    for(int i = startIndex; i <strlen(line); i++) {
        if (line[i] < '0' || line[i] > '9')
            return false;
    }
    return true;
}

int main() {
    int a, b;
    char inA[BUFFER_SIZE], inB[BUFFER_SIZE];

    printf("Input integer a:\n");
    gets(inA);
    if(!isInteger(inA)) {
        printf("Error: invalid characters");
        return 0;
    }
    a = atoi(inA);

    printf("Input integer b:\n");
    gets(inB);
    if(!isInteger(inB)) {
        printf("Error: invalid characters");
        return 0;
    }
    b = atoi(inB);

    swap(&a, &b);

    printf("After swapping:\n");
    printf("a = %d\nb = %d", a, b);

    return 0;
}
