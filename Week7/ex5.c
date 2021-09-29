#include <stdio.h>
#include <stdlib.h>

int main () {
    char **s = (char**)malloc(sizeof(char*));   // 1st bug: we should allocate memory for s
    char foo[] = "Hello World";
    *s = foo;
    printf("s is %s\n", *s);    // 2nd bug: we should dereference char** to output a char*

    s[0] = foo;
    printf("s[0] is %s\n", s[0]);

    free(s);

    return(0);
}