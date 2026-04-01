#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    char input[1024];
    while (fgets(input, 1024, stdin) != NULL) {
        printf("program 2 received: %s", input);
    }
    return 0;
}

