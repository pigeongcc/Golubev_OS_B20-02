#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

void printFigure(int n, int type) {
    // right triangle
    if(type == 1) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= i; j++)
                putchar('*');
            putchar('\n');
        }
    }
        // triangle
    else if (type == 2) {
        for(int i = 1; i <= floor(n/2); i++) {
            for(int j = 1; j <= i; j++)
                putchar('*');
            putchar('\n');
        }
        if(n % 2 == 1) {
            for (int j = 1; j <= floor(n / 2) + 1; j++)
                putchar('*');
            putchar('\n');
        }
        for(int i = floor(n/2); i > 0; i--) {
            for(int j = 1; j <= i; j++)
                putchar('*');
            putchar('\n');
        }
    }
        // rectangle
    else if (type == 3) {
        for(int i = 1; i <= n; i++) {
            for (int i = 1; i <= n; i++)
                putchar('*');
            putchar('\n');
        }
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
    int type, n;

    if( argc == 3 ) {

        char* n = argv[1];
        char* type = argv[2];

        if(!isInteger(n) || !isInteger(type)) {
            printf("Error: two integer arguments expected\n");
            return 0;
        }

        int nInt, typeInt;
        sscanf(n, "%d", &nInt);
        sscanf(type, "%d", &typeInt);

        if(typeInt < 1 || typeInt > 3) {
            printf("Error: the second argument (figure type) must be either 1, 2, or 3\n");
            return 0;
        }

        printFigure(nInt, typeInt);
    }
    else if( argc > 3 ) {
        printf("Error: too many arguments supplied\n");
    }
    else {
        printf("Error: two arguments expected\n");
    }

    return 0;
}
