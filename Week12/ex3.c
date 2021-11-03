#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define NUM_OF_EVENTS 2
#define MAX_SHORTCUT_LENGTH 3

char * event_name[NUM_OF_EVENTS] ={ "RELEASED", "PRESSED" };

void print_string(char * output) {
    FILE * fp = fopen("./ex3.txt", "a");
    fprintf(fp, "%s", output);
    fclose(fp);
}

void append_shortcut_buffer(int val, int * shortcut_buffer) {
    for(int i = MAX_SHORTCUT_LENGTH - 1; i >= 1; i --)
        shortcut_buffer[i] = shortcut_buffer[i-1];
    shortcut_buffer[0] = val;
}

void check_shortcut(const int * shortcut_buffer) {
    // PE shortcut
    if(shortcut_buffer[1] == 25 && shortcut_buffer[0] == 18)
        print_string("I passed the Exam!\n");

    // CAP shortcut
    if(shortcut_buffer[2] == 46 && shortcut_buffer[1] == 30 && shortcut_buffer[0] == 25)
        print_string("Get some cappuccino!\n");

    // YES shortcut
    if(shortcut_buffer[2] == 21 && shortcut_buffer[1] == 18 && shortcut_buffer[0] == 31)
        print_string("Prof.Succi: \"You passed the oral!\"\n");
}

int main() {

    char * input_file = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    int f = open(input_file, O_RDONLY);

    // checking if the file is opened correctly
    // the error may be thrown while not using the superuser rights
    if(f == -1) {
        printf("Error while opening %s\n", input_file);
        return EXIT_FAILURE;
    }

    struct input_event ie;
    ssize_t n;

    printf("Shortcuts:\n");
    printf("P + E -> \t 'I passed the Exam!'\n");
    printf("C + A + P -> \t 'Get some cappuccino!'\n");
    printf("Y + E + S -> \t 'Prof.Succi: \"You passed the oral!\"'\n");

    int * shortcut_buffer = malloc(sizeof(int) * MAX_SHORTCUT_LENGTH);
    for(int i = 0; i < MAX_SHORTCUT_LENGTH; i ++)
        shortcut_buffer[i] = -1;

    // endless loop for capturing the events
    while(1) {
        n = read(f, &ie, sizeof(ie));
        // break in case of error
        if(n == (ssize_t)(-1)) {
            if(errno == EINTR)
                continue;
            else
                break;
        }

        if(ie.type == EV_KEY && ie.value == 1) {
            append_shortcut_buffer((int) ie.code, shortcut_buffer);
            check_shortcut(shortcut_buffer);
        }
    }

    return 0;
}
