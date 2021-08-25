#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 100

int main() {
    char string[BUFFER_SIZE];
    gets(string);
    int len = strlen(string);

    for(int i = 0; i < len; i++) {
        putchar(string[len - i - 1]);
    }

    return 0;
}
