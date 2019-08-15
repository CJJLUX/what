#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    apple = 1,
    apple1,
} fuilt;

int main(int argc, char **argv)
{
    int put_buf = -1;

    put_buf = atoi(argv[1]);
    switch(put_buf) {
        case apple:
            printf("123\n");
            break;
        case apple1:
            printf("456\n");
            break;
        default:
            break;
    }

    exit(0);
}

