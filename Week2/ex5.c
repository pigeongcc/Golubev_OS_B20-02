#include <stdio.h>
#include <math.h>

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

int main() {
    int type, n;
    printf("Input the figure type:\n"
           "1 - right triangle\n"
           "2 - triangle\n"
           "3 - rectangle\n");
    scanf("%d", &type);

    printf("Input the depth:\n");
    scanf("%d", &n);

    printFigure(n, type);

    return 0;
}
