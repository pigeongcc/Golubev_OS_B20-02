#include <stdio.h>
#include <stdlib.h>
#include <linux/input.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define NUM_OF_EVENTS 2

char * event_name[NUM_OF_EVENTS] ={ "RELEASED", "PRESSED" };

void print_event(struct input_event ie) {
    FILE * fp = fopen("./ex2.txt", "a");
    fprintf(fp, "%s 0x%04x (%d)\n", event_name[ie.value], (int) ie.code, (int) ie.code);
    fclose(fp);
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

    FILE *fp;
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

        // print the event info into the file ex2.txt
        if(ie.type == EV_KEY && ie.value >= 0 && ie.value < NUM_OF_EVENTS) {
            print_event(ie);
        }
    }


    return 0;
}
