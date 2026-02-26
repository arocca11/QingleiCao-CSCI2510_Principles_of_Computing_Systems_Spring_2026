// Anthony Rocca
//February 17, 2026
//Hello world with linux write() call
#include <unistd.h>

int main(int argc, char* argv[]) {
    write(STDOUT_FILENO, "Hello, world!\n", 14);
    return 0;
    }
