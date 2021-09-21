#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* threadFunc(void* thread_data){
    printf(">> Thread %i: \"I'm running!\"\n", *((int*)thread_data));
    pthread_exit(0);
}

int main(){
    int n;
    printf("Enter the number of threads n: ");
    scanf("%d", &n);

    for(int i = 1; i <= n; i++) {
        void* thread_data = malloc(2 * sizeof(int*));
        *((int*)thread_data) = i;

        pthread_t thread;

        if(pthread_create(&thread, NULL, threadFunc, thread_data) != 0) {
            printf("Error while creating thread %i.\n", *((int*)thread_data));
            pthread_exit(0);
            return 1;
        }
        else {
            pthread_join(thread, NULL);
            printf("Thread %i has been created.\n", *((int*)thread_data));
        }
    }

    return 0;
}