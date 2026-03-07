#include <stdio.h>
#include <stdlib.h>

void printReverse(char* string) {
    int x = 0;
    while (string[x] != '\0') {
        x++;
        }
    for (int i = x - 1; i >= 0; i--) {
        printf("%c\n", string[i]);
        }
    }
//this recursive function results in o(2^n).. inefficent 
int fib_recursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n-1) + fib_recursive(n-2);
    }

int fib_iterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int y = 0;
    int z = 1;
    int cur;
    //linear scale due to the single for loop.. efficient.. updating the variables at the end allows for minimum memory
    for (int i = 2; i <= n; i++) {
        cur = y + z;
        y = z;
        z = cur;
        }
        return cur;
    }

char* reverseString(char* input) {
    int x = 0;
    while (input[x] != '\0') {
        x++;
    }

    char* output = (char*)malloc(x + 1);

    for (int i = 0; i < x; i++) {
        output[i] = input[x - 1 - i];
    }

    output[x] = '\0';

    return output;
}

int main () {
    char *messagePtr = "HELLOWORLD!";
    printf("%s\n", messagePtr);
    for (int i = 0; messagePtr[i] != '\0'; i++) {
        printf("%c\n", messagePtr[i]);
        }
    printf("%c\n", *messagePtr);
    printf("%c\n", *(messagePtr + 1));
    printf("%c\n", *(messagePtr + 2));
    printf("%c\n", *(messagePtr + 3));
    for (int i = 0; *(messagePtr + i) != '\0'; i++) {
        printf("%c\n", *(messagePtr + i));
        }
    int i = 0;
    while (messagePtr[i] != '\0') {
        printf("%c\n", messagePtr[i]);
        i++;
        }
    printReverse(messagePtr);
    printf("recsurive: %d\n", fib_recursive(5));
    printf("iterative: %d\n", fib_iterative(5));
    char* reversedMessage = reverseString(messagePtr);
    printf("reverse string w/ malloc: %s\n", reversedMessage);
    free(reversedMessage);
    return 0;
    }
