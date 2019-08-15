#ifndef __UART_CLOCK
#define __UART_CLOCK

#define Base_Address_UART        0xC0000000

#define UARTCLKGEN0L        (*(volatile unsigned int *)(Base_Address_UART + 0xA8004))
#define UARTCLKGENB        (*(volatile unsigned int *)(Base_Address_UART + 0xA8000))

extern void uart_clock_print(void);

#endif

