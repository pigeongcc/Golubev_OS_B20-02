#include <stdio.h>
#include "string.h"
#include "stdbool.h"

void printTriangle(int n) {
    for(int i = 1; i <= n; i++) {
        int spaceCounter = n - i - 1;
        for(int j = 0; j <= spaceCounter; j++)
            putchar(' ');
        for(int j = 1; j <= i; j++)
            putchar('*');
        for(int j = 1; j < i; j++)
            putchar('*');
        putchar('\n');
    }
}

bool isInteger(char* line) {
    for(int i = 0; i <strlen(line); i++) {
        if (line[i] < 48 || line[i] > 57)
            return false;
    }
    return true;
}

int main(int argc, char *argv[]) {

    if( argc == 2 ) {

        char* string = argv[1];

        if(!isInteger(string)) {
            printf("Error: integer argument expected\n");
            return 0;
        }

        int n;
        sscanf(argv[1], "%d", &n);

        printTriangle(n);
    }
    else if( argc > 2 ) {
        printf("Error: too many arguments supplied\n");
    }
    else {
        printf("Error: one argument expected\n");
    }

    return 0;
}
