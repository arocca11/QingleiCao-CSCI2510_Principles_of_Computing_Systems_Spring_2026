#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define bufferSize 4096

int main(int argc, char *argv[]) {
    //checks for correct number of command line arguments which is 2
    if (argc != 2) {
        fprintf(stderr, "use %s <filename>\n", argv[0]);
        exit(-1);
    }

    //opens the file instead of relaying on STDIN
    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("error opening file");
        exit(-1);
    }

    char buffer[bufferSize];
    ssize_t bytes_read;

    while (1) {
        bytes_read = read(fd, buffer, bufferSize);

        if (bytes_read == 0) {
            break;
        }

        if (bytes_read == -1) {
            perror("error reading file");
            close(fd);
            exit(-1);
        }

        write(STDOUT_FILENO, buffer, bytes_read);
    }
    close(fd);
    return 0;
}
