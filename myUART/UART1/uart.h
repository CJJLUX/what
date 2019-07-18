#ifndef __UART_H__
#define __UART_H__

//UARTTXD  DB18
//UARTRXD  DB14
#define BASE_ADDRESS   			     0xC0010000
#define GPIO_D          		    (BASE_ADDRESS + 0xD000)

#define GPIODOUT                      (*(volatile unsigned int *)(GPIO_D + 0x0000)) 
#define GPIODOUTENB                   (*(volatile unsigned int *)(GPIO_D + 0x0004)) 
#define GPIODALTFN0                   (*(volatile unsigned int *)(GPIO_D + 0x0020)) 
#define GPIODALTFN1                   (*(volatile unsigned int *)(GPIO_D + 0x0024)) 
#define GPIOD_PULLENB                 (*(volatile unsigned int *)(GPIO_D + 0x0060))
#define GPIOD_PULLENB_DISABLE_DEFAULT (*(volatile unsigned int *)(GPIO_D + 0x0064))


//把这两个管脚配置为复用功能
//GPIO_D18
//GPIO_D14


//UART0
#define UART0_BaseAddress        0xC00A0000 
#define ULCON0                  (*(volatile unsigned int *)(UART_BaseAddress + 0x1000))
#define UCON0                   (*(volatile unsigned int *)(UART_BaseAddress + 0x1000))
#define UFCON0                  (*(volatile unsigned int *)(UART_BaseAddress + 0x1008)) 
#define UMCON0                  (*(volatile unsigned int *)(UART_BaseAddress + 0x100C))
#define UTRSTAT0                (*(volatile unsigned int *)(UART_BaseAddress + 0x1010))
#define UTXH0                   (*(volatile unsigned int *)(UART_BaseAddress + 0x1020))
#define URXH0                   (*(volatile unsigned int *)(UART_BaseAddress + 0x1024))
#define UBRDIV0                 (*(volatile unsigned int *)(UART_BaseAddress + 0x1028))
#define UFRACVAL0               (*(volatile unsigned int *)(UART_BaseAddress + 0x102C))



extern void uart0_init(void);
extern void uart0_send(char c);
extern void uart0_recv(void);

extern void uputchar(char c);
extern char ugetchar(void);
extern void uputs(char *s);
extern char *ugets(char *s, int buf_len);
extern int uprintf(const char *fmt, ...);

endif

