#include <stdio.h>

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

int main() {
    int n;
    scanf("%d", &n);

    printTriangle(n);

    return 0;
}
