#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "sys/wait.h"

#define BUFFER_SIZE 256

void execute_command(char* input) {
    // splitting the input by spaces to get the command and the arguments

    // word is a part of input string surrounded by whitespaces
    // so, the 1st word is the command to execute, and others are arguments
    char* word;

    // copy the input string since the splitter changes the passed string
    char input_to_split[BUFFER_SIZE];
    strcpy(input_to_split, input);

    // array of arguments
    char* argv[BUFFER_SIZE];
    int num_of_args = 0;

    // the first word is the command itself
    word = strtok(input, " ");
    char* commandWord = malloc(sizeof(char));
    strcpy(commandWord, word);

    char* command = malloc(sizeof(char));
    strcat(command, commandWord);

    printf("COMMAND: %s\n", command);

    // run the string splitter
    while (word != NULL)
    {
        char* new_arg = malloc(sizeof(char));
        strcpy(new_arg, word);
        argv[num_of_args] = new_arg;
        printf("ARG: %s\n", argv[num_of_args]);
        num_of_args++;
        word = strtok (NULL, " ");
    }
    // adding a null pointer to argv
    argv[num_of_args] = NULL;
    num_of_args++;

    // run execvp (it's easier t ouse compared to execve)
    if(execvp(command, argv) < 0)
        printf("Error while running execvp. Please check if the input is appropriate for the terminal format.\n");
}

int main() {

    char input[BUFFER_SIZE] = " ";
    while(strcmp(input,"exit") != 0) {
        fgets(input, sizeof(input), stdin);

        // replace the '\n' symbol with end of a string symbol
        input[strlen(input)-1] = '\0';

        pid_t pid;  // process ID
        pid = fork();

        // child case
        if(pid == 0) {
            // background case: replace the '&' symbol with end of a string symbol
            if(input[strlen(input) - 1] == '&')
                input[strlen(input) - 1] = '\0';
            execute_command(input);
        }
        // parent case
        else
            // background process case
            if(input[strlen(input) - 1] == '&')
                wait(NULL);     // wait for a child process to execute
    }

    return 0;
}
