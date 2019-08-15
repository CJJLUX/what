#include <stdio.h>
#include <stdlib.h>
#include "clock.h"


void uart_clock_print(void)
{
    printf("UARTCLKGEN0L: %#x\n", UARTCLKGEN0L);
    printf("UARTCLKGENB: %#x\n", UARTCLKGENB);
}


