#include "uart.h"

#define BUFSIZE     1024

int main()
{
    char *word = 'A';
    int count = 0;
    char *buf;

    uart0_init();
    
    buf = (char *)malloc(sizeof(BUFSIZE));

    while (i = 0; i < count % 10; i++) {
        *word = *word + i;
        uart0_send(word);
        buf = uart0_recv();
        count += 1;
        buf = buf + count;
        if (count > 1024) {
            count = 0;
        }
    }

    return 0;
}

