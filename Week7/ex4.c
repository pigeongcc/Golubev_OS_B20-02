#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

void * myRealloc(void * ptr, size_t size) {
    if(ptr == NULL)
        return malloc(size);

    if(size == 0) {
        free(ptr);
        return NULL;
    }

    // perform a new memory allocation
    void * newPtr = malloc(size);

    // copy the existing data to the new memory
    memcpy(newPtr, ptr, size);

    // free old memory
    free(ptr);

    return newPtr;
}

int main(){
    printf("I took the code of ex3 to test ex4. myRealloc function is used instead of realloc.\n");

    //Allows you to generate random number
    srand(time(NULL));

    // Allows user to specify the original array size, stored in variable n1.
    printf("Enter original array size:");
    int n1=0;
    scanf("%d",&n1);

    //Create a new array of n1 ints
    int* a1 = malloc(n1 * sizeof(int));
    printf("Old size from main: %zu\n", sizeof(a1));
    printf("Or: %zu\n", n1 * sizeof(int));
    printf("Int size from main: %zu\n", sizeof(int));
    int i;
    for(i=0; i<n1; i++){
        //Set each value in a1 to 100
        *(a1+i)=100;

        //Print each element out (to make sure things look right)
        printf("%d ", *(a1+i));
    }

    //User specifies the new array size, stored in variable n2.
    printf("\nEnter new array size: ");
    int n2=0;
    scanf("%d",&n2);

    //Dynamically change the array to size n2
    a1 = myRealloc(a1, n2 * sizeof(int));

    for(i=0; i<n2;i++){
        //Print each element out (to make sure things look right)
        printf("%d ", *(a1+i));
    }
    printf("\n");

    //Done with array now, done with program :D

    return 0;
}
