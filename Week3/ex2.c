#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubblesort(int* ptr, int size) {
    for(int i = 0; i < size-1; i++)
        for(int j = 0; j < size-i-1; j++) {
            if (*(ptr + j) > *(ptr + j + 1))
                swap(ptr + j, ptr + j + 1);
        }
}

bool isInteger(char* line) {
    int startIndex = 0;
    int len = strlen(line);

    // for negative numbers (if starts with '-')
    if(line[0] == '-') {
        if (len > 1)
            startIndex = 1;
        else
            return false;
    }
    // if starts with zero
    if(line[startIndex] == '0' && len > 1)
        return false;

    for(int i = startIndex; i < len; i++) {
        if (line[i] < '0' || line[i] > '9')
            return false;
    }
    return true;
}

int main() {

    char input[100];
    int BUFFER_SIZE;

    printf("Input the size of an array:\n");

    gets(input);
    if(!isInteger(input)) {
        printf("Error: invalid characters. Please input integers only.");
        return 0;
    }

    BUFFER_SIZE = atoi(input);
    if(BUFFER_SIZE <= 0) {
        printf("Error: array size must be a positive integer.");
        return 0;
    }

    int arr[BUFFER_SIZE];

    printf("Input the elements of the array:\n");
/*
    for(int i = 0; i < BUFFER_SIZE; i++) {
        gets(input);
        if(!isInteger(input)) {
            printf("Error: invalid characters. Please input integers only.");
            return 0;
        }
        arr[i] = atoi(input);
    }
    */
    for(int i=0; i < BUFFER_SIZE; i++){
        scanf("%s", input);
        if(!isInteger(input)) {
            printf("Error: invalid characters. Please input integers only.");
            return 0;
        }
        arr[i] = atoi(input);
    }

    bubblesort(arr, BUFFER_SIZE);
    printf("Sorted array:\n");

    for(int i = 0; i < BUFFER_SIZE; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
