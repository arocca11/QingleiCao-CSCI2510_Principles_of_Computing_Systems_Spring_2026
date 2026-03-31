#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char buffer[1024];
    int max_args = 15;
    int max_argv_size = max_args + 2;
    char* cmd;
    char* my_argv[max_argv_size];
    printf("Enter a command to execute: ");
    if (fgets(buffer, 1024, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        cmd = strtok(buffer, " ");
        my_argv[0] = cmd;
        int i = 1;
        char* res = strtok(NULL, " ");
        while (res != NULL) {
            my_argv[i] = res;
            i++;
            res = strtok(NULL, " ");
        }
        my_argv[i] = NULL;
        execvp(cmd, my_argv);
        printf("execvp failed. command not found");
        //printf("you entered: %s\n", buffer);
        //char* token = strtok(buffer, " ");
        //printf("exercise 4 first token: %s\n", token);

        //while (token != NULL) {
            //printf("%s\n", token);
            //token = strtok(NULL, " ");
        //}
    }
    return 0;
}
