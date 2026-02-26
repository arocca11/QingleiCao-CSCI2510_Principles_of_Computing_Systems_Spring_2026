#include <stdio.h>
#include <unistd.h>

//buffersize originally 200
#define bufferSize 4096

int main() {
	//storing the bytes read from STDIN_FILENO (0) in this array
    char buffer[bufferSize];
    ssize_t bytes_read;

    while (1) {
		//read up to bufferSize bytes from STDIN_FILENO (0) into the buffer array
        bytes_read = read(STDIN_FILENO, buffer, bufferSize);

		//if 0 terminates the loop
        if (bytes_read == 0) {
            break;
        }

        //deals with the errors
        if (bytes_read < 0) {
            return 1; 
        }
		//write the bytes read from the buffer array to STDOUT_FILENO (1)
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    return 0;
}