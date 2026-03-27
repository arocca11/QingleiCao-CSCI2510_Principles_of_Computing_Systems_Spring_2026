#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

void exercise_1() {
    printf("\n=== Exercise 1 ===\n");
    printf("My PID is: %d\n", getpid());
}

void exercise_234() {
    printf("\n=== Exercise 2,3,4 ===\n");
    pid_t child_pid = fork();

    if (child_pid == 0) {
        printf("child PID: %d\n", getpid());
        exit(0);
    } 
    else if (child_pid > 0) {
        printf("parent PID: %d and the child PID is %d\n", getpid(), child_pid);
        wait(NULL);
    }
    else {
        printf("Fork failed\n");
    }
}

void exercise_5() {
    printf("\n=== exercise 5 ===\n");
    pid_t child_pid = fork();

    if (child_pid == 0) {
        //sleep(5);
        printf("child PID: %d\n", getpid());
        exit(0);
    }
    else if (child_pid > 0) {
        printf("parent PID: %d, and child PID: %d\n", getpid(), child_pid);
    }
    else {
        printf("fork failed\n");
    }
}

void exercise_6() {
    printf("\n=== exercise 6 waitpid ===\n");
    pid_t child_pid = fork();

    if (child_pid == 0) {
        sleep(3);
        printf("child pid: %d\n", getpid());
        exit(0);
    }
    else if (child_pid > 0) {
        printf("parent pid: %d.. waiting on child %d\n", getpid(), child_pid);
        waitpid(child_pid, NULL, 0);
        printf("child is finished parent now exiting\n");
    }
    else {
        printf("fork failed\n");
    }
}

void exercise_78() {
    printf("\n=== exercise 7 and 8 ===\n");
    pid_t child_pid = fork();

    if (child_pid == 0) {
        printf("child PID: %d will containt 'ls -l'..\n", getpid());

        char* child_argv[] = {"ls", "-l", NULL};
        char* child_prog = child_argv[0];

        execvp(child_prog, child_argv);
        printf("execvp failed\n");
        exit(1);
    }
    else if (child_pid > 0) {
        printf("parent PID: %d .. waiting on child to run ls .. \n\n", getpid());
        waitpid(child_pid, NULL, 0);
        printf("\nparent: the ls command is complete.. now exiting\n");
    }
    else {
        printf("fork failed\n");
    }
}






int main() {
    exercise_1();
    sleep(2);
    exercise_234();
    sleep(2);
    exercise_5();
    sleep(2);
    exercise_6();
    sleep(2);
    exercise_78();
    return 0;
}
