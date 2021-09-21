#include <stdio.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int producer_is_sleeping = 0;
int consumer_is_sleeping = 0;
int numberOfConsumerCalls = 0;

// max number of elements in the buffer is BUFFER_SIZE
int buf[BUFFER_SIZE];
int count = 0;

void* thread_func_producer(void* thread_data){
    while(1) {
        if(count == BUFFER_SIZE) producer_is_sleeping = 1;
        while(producer_is_sleeping);

        *(buf + count) = 8;
        count++;

        if(count == 1) consumer_is_sleeping = 0;     // wakeup the consumer
    }
}

void* thread_func_consumer(void* thread_data){
    while(1) {
        numberOfConsumerCalls++;
        if(numberOfConsumerCalls % 5 == 0) printf("Consumer has been called %i times.\n", numberOfConsumerCalls);

        if(count == 0) consumer_is_sleeping = 1;
        while(consumer_is_sleeping);

        *(buf + count) = 0;
        count--;

        if(count == BUFFER_SIZE-1) producer_is_sleeping = 0;   // wakeup the producer
    }
}

int main(){

    pthread_t producer_th, consumer_th;

    if(pthread_create(&producer_th, NULL, thread_func_producer, NULL) +
        pthread_create(&consumer_th, NULL, thread_func_consumer, NULL)!= 0) {
        printf("Error while creating threads.\n");
        pthread_exit(0);
        return 1;
    }
    else {
        printf("The threads has been started.\n");
    }

    pthread_join(producer_th, NULL);
    pthread_join(consumer_th, NULL);

    return 0;
}