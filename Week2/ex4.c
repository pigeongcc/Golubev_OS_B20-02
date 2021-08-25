#include <stdio.h>

void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

int main() {
    int a, b;
    printf("Input integer a:\n");
    scanf("%d", &a);
    printf("Input integer b:\n");
    scanf("%d", &b);

    swap(&a, &b);

    printf("a = %d\nb = %d", a, b);

    return 0;
}
