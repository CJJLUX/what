#include "uart.h"

#define BUFSIZE     1024

int main(int argc, char **argv)
{
    int count = 0;
    int i = 0;
    char buf_arr[BUFSIZE] = {0};
    char word = 'A';
    
    printf("UARTCLKGEN0L = %#x\n", UARTCLKGEN0L);
    printf("CLKGENENB = %#x\n", CLKGENENB);

    uart0_init();
    printf("----------uart0_init\n");
    while (1) {
        for (i = 0; i < count % 10; i++) {
            word = word + 1;
            uart0_send(word);

            buf_arr[count] = uart0_recv();
            count += 1;
            if (count == 1024) {
                break;
            }
            printf("%c\n", *(buf_arr + count));
        }
    }
    return 0;
}

