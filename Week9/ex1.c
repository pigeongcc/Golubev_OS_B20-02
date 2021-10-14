#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

#define NUM_OF_BITS_PER_PAGEFRAME 16
unsigned long long PAGEFRAME_CONST;
int hit = 0;
int miss = 0;

struct pageframe {
    unsigned long long counter;
    int current_page_id;
};

int bin_to_dec(unsigned long long num) {
    int ans = 0;
    int digit = 0;

    while(num > 0) {
        if(num % 10)
            ans +=  1 << digit;     // 2^digit
        digit++;
        num /= 10;
    }

    return ans;
}

void page_replacement(struct pageframe * main_memory, int num_pageframes, int new_page_id) {
    int already_in_memory_index = -1;
    int min_counter_index = 0;

    for(int i = 0; i < num_pageframes; i++) {
        int counter_i_dec = bin_to_dec(main_memory[i].counter);
        printf("i = %d id = %d %d\n", i, main_memory[i].current_page_id, counter_i_dec);

        // CASE 1 (HIT): if new_page is already in memory, then add 1 to its counter left-most digit
        if(main_memory[i].current_page_id == new_page_id) {
            already_in_memory_index = i;
            hit++;
            break;
        }

        // CASE 2 (MISS): if new_page is not in memory yet, then we replace the page with the minimum counter
        int counter_min_dec = bin_to_dec(main_memory[min_counter_index].counter);
        if(counter_i_dec < counter_min_dec)
            min_counter_index = i;
    }
    printf("Current page number: %d\n\n", new_page_id);

    // CASE 1 (HIT)
    int replace_index = already_in_memory_index;
    // CASE 2 (MISS)
    if(already_in_memory_index == -1) {
        replace_index = min_counter_index;
        miss++;
    }

    // Replacing & updating loop
    for(int i = 0; i < num_pageframes; i++) {
        if(i == replace_index) {
            main_memory[i].current_page_id = new_page_id;
            main_memory[i].counter = PAGEFRAME_CONST + main_memory[i].counter / 10;
        }
        else {
            main_memory[i].counter /= 10;
        }
    }
}

int main() {
    PAGEFRAME_CONST = (unsigned long long) pow(10, NUM_OF_BITS_PER_PAGEFRAME - 1);

    int n;
    printf("Input the number of pageframes: ");
    scanf("%d", &n);

    struct pageframe * my_main_memory = malloc(n * sizeof(struct pageframe));

    char buff[255];
    FILE *fp = fopen("input.txt", "r");
    if( fp == NULL ) {
        fprintf(stderr, "Couldn't open: %s\n", strerror(errno));
        exit(1);
    }

    while(1) {
        if(fscanf(fp, "%s", buff) == EOF)
            break;

        int page_id = (int) strtol(buff, NULL, 10);

        page_replacement(my_main_memory, n, page_id);
    }

    float ratio = (float)hit/miss;
    printf("hit = %d miss = %d ratio = %f", hit, miss, ratio);

    fclose(fp);

    return 0;
}
