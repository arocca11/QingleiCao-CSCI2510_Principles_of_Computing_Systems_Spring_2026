#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    printf("parent: spawning...\n\n");

    int fd[2];
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid_t child1_pid = fork();
    if (child1_pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        char* cmd1 = "./program1";
        char* argv1[] = {"program1", NULL};
        execvp(cmd1, argv1);
        perror("error exe program1");
        exit(1);
    }

    pid_t child2_pid = fork();
    if (child2_pid == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        char* cmd2 = "./program2";
        char* argv2[] = {"program2", NULL};
        execvp(cmd2, argv2);
        perror("error exe program2");
        exit(1);
    }
    close(fd[0]);
    close(fd[1]);

    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);
    printf("\nparent: both children done. exiting.\n");
    return 0;
}
