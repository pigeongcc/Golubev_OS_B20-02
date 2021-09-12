#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 256

int main() {
    char input[BUFFER_SIZE];
    while(1) {
        fgets(input, sizeof(input), stdin);
        system(input);
    }
    return 0;
}
