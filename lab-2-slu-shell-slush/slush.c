#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LINE 256

void sigint_handler(int sig) {
    //ignore SIGINT to prevent the shell from exiting on Ctrl+C
    printf("\n");
}

void execute_pipeline(char* segments [], int index, int total_segments) {
    char *argv[16];
    int arg_count = 0;

    //tokenize the segment by spaces to get the command and args
    char* arg_token = strtok(segments[index], " ");
    while (arg_token != NULL && arg_count < 15) {
        argv[arg_count] = arg_token;
        arg_count++;
        arg_token = strtok(NULL, " ");
    }
    argv[arg_count] = NULL; //null-terminate the argument list

    //when we reach the last segment - execute normally
    if (index == total_segments - 1) {
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(1);
    }

    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        //move to the right side of the pipe for the next command..
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execute_pipeline(segments, index + 1, total_segments);
    } else {
        //move to the left side of the pipe for the current command..
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        //execute the current command
        execvp(argv[0], argv);
        perror(argv[0]);
        exit(1);
    }
}

int main() {
    char buffer[MAX_LINE];
    signal(SIGINT, sigint_handler);
    //keep the shell going with an infinite loop
    while (1) {
        //print the prompt immediately
        printf("slush> ");
        fflush(stdout);
        
        //read the user input from stdin if the user hits Ctrl+D (EOF), fgets will return NULL, so we can check for that to exit gracefully
        if (fgets(buffer, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break;
        }

        //strip the newline character from the end of the input
        buffer[strcspn(buffer, "\n")] = '\0';

        //if the user presses enter without text then ask for input again
        if (strlen(buffer) == 0) {
            continue;
        }

        //tokenize and store in an array
        char* segments[256];
        int pipeline_count = 0;
        char* token = strtok(buffer, "(");

        
        //loop through the tokens and print them out
        while (token != NULL) {
            segments[pipeline_count++] = token;
            token = strtok(NULL, "(");
        }

        //check if the first segment is a cd command and handle it
        char first_segment_copy[MAX_LINE];
        //make a copy of the first segment to avoid modifying the original buffer
        strncpy(first_segment_copy, segments[0], MAX_LINE);
        //tokenize the first segment to get the command and its argument
        char* cmd = strtok(first_segment_copy, " ");
        //get the directory argument for cd if it exists
        char* dir = strtok(NULL, " ");

        if (cmd != NULL && strcmp(cmd, "cd") == 0) {
            if ((pipeline_count > 1) || (dir == NULL)) {
                fprintf(stderr, "cd usage: cd <directory>\n");
            } else {
                if (chdir(dir) != 0) {
                    perror("cd");
                }
            }
            continue;
        }
        else {
            pid_t pid = fork();
                if (pid == -1) {
                    perror("fork failed");
                } else if (pid == 0) {
                    execute_pipeline(segments, 0, pipeline_count);
                } else {
                    waitpid(pid, NULL, 0);
                }
       }
    }
}