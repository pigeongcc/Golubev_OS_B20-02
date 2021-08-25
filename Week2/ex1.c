#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int intVar;
    float floatVar;
    double doubleVar;

    printf("Integer is of size %d bytes and has a max value of %d\n", sizeof(intVar), INT_MAX);
    printf("Float is of size %d bytes and has a max value of %f\n", sizeof(floatVar), FLT_MAX);
    printf("Double is of size %d bytes and has a max value of %f\n", sizeof(doubleVar), DBL_MAX);

    return 0;
}
