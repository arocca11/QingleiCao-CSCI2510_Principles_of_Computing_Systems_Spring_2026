//Runlength compression in C
// Usage: ./rle <input file> <output file> <runlength> <mode>
//Where mode=0 is compress and mode=1 is decompress
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char **argv) {
    //check the argument count must have 5 things
    if (argc !=5) {
        fprintf(stderr, "%s must have 5 arguments\n", argv[0]);
        exit(-1);
    }

    //parse the arguments
    //we can skip argv[0] because it is the name
    //argv[1] is the input, ill declare a char pointer
    //argv[2] is the output, ill delcare a char pointer here as well
    //for argv[3] and argv[4] im converting the string to an integer
    char *input_file = argv[1];
    char *output_file = argv[2];
    int c_length = atoi(argv[3]);
    int mode = atoi(argv[4]);
    
    //make sure the compression length is 1 or greater
    if (c_length < 1) {
        fprintf(stderr, "error: compression length must be 1 or greater.\n");
        exit(-1);
    }
    
    //make sure the mode is either 0 or 1
    if (mode !=0 && mode !=1) {
        fprintf(stderr, "error: mode must be 0 or 1.\n");
        exit(-1);
    }

    //make a system call to open the output file
    int file_in = open(input_file, O_RDONLY);
    if (file_in < 0) {
        perror("error opening file");
        exit(-1);
    }

    //make system call to open output file
    int file_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (file_out < 0) {
        perror("error opening file");
        close(file_in);
        exit(-1);
    }

    if (mode == 0) {
        //set buffers
        char *curr_pattern = malloc(c_length);
        char *next_pattern = malloc(c_length);
        
        //set counter to 1 byte
        unsigned char count = 1;

        //read first heap
        ssize_t curr_bytes_read = read(file_in, curr_pattern, c_length);
        
        //if the file is empty do nothing
        if (curr_bytes_read > 0) {
            while (1) {
                ssize_t next_bytes_read = read(file_in, next_pattern, c_length);
                if (next_bytes_read <= 0) {
                    write(file_out, &count, 1);
                    write(file_out, curr_pattern, curr_bytes_read);
                    break;
                }
                //check if there is a match
                int is_match = 1;
                if (next_bytes_read != curr_bytes_read) {
                    is_match = 0;
                } else {
                    for (int i = 0; i < curr_bytes_read; i++) {
                        if (curr_pattern[i] != next_pattern[i]) {
                            is_match = 0;
                            break;
                        }
                    }
                }

                //run-length logic
                if (is_match && count < 255) {
                    count++;
                } else {
                    write(file_out, &count, 1);
                    write(file_out, curr_pattern, curr_bytes_read);
                    //reset
                    count = 1;
                    curr_bytes_read = next_bytes_read;
                    memcpy(curr_pattern, next_pattern, c_length);
                }
            }
        }
        //clear the memory
        free(curr_pattern);
        free(next_pattern);
    }

    if (mode == 1) {
        unsigned char count;
        char *patt = malloc(c_length);
        while (read(file_in, &count, 1) > 0) {
            ssize_t bytes_read = read(file_in, patt, c_length);
            if (bytes_read <= 0) {
                break;
            }

            for (int i = 0; i < count; i++) {
                write(file_out, patt, bytes_read);
            }
        }
        free(patt);
    }
}
