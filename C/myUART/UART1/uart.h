#ifndef MYUART_H__
#define MYUART_H__


#define UARTCLKGEN0L	(*(volatile unsigned int *)(0xC00A9004))
#define CLKGENENB		(*(volatile unsigned int *)(0xC00A9000))

//UARTTXD  DB18
//UARTRXD  DB14
//#define BASE_ADDRESS   			     0xC0010000
//#define GPIO_D          		    (BASE_ADDRESS + 0xD000)

//#define 0xC001D000   			     0xC001D000
#define GPIODOUT                      (*(volatile unsigned int *)(0xC001D000)) 
#define GPIODOUTENB                   (*(volatile unsigned int *)(0xC001D004)) 
#define GPIODALTFN0                   (*(volatile unsigned int *)(0xC001D020)) 
#define GPIODALTFN1                   (*(volatile unsigned int *)(0xC001D024)) 
#define GPIOD_PULLENB                 (*(volatile unsigned int *)(0xC001D060))
#define GPIOD_PULLENB_DISABLE_DEFAULT (*(volatile unsigned int *)(0xC001D064))


//把这两个管脚配置为复用功能
//GPIO_D18
//GPIO_D14


//UART0
#define UART0_BaseAddress        0xC00A0000 
#define ULCON0                  (*(volatile unsigned int *)(UART0_BaseAddress + 0x1000))
#define UCON0                   (*(volatile unsigned int *)(UART0_BaseAddress + 0x1000))
#define UFCON0                  (*(volatile unsigned int *)(UART0_BaseAddress + 0x1008)) 
#define UMCON0                  (*(volatile unsigned int *)(UART0_BaseAddress + 0x100C))
#define UTRSTAT0                (*(volatile unsigned int *)(UART0_BaseAddress + 0x1010))
#define UTXH0                   (*(volatile unsigned int *)(UART0_BaseAddress + 0x1020))
#define URXH0                   (*(volatile unsigned int *)(UART0_BaseAddress + 0x1024))
#define UBRDIV0                 (*(volatile unsigned int *)(UART0_BaseAddress + 0x1028))
#define UFRACVAL0               (*(volatile unsigned int *)(UART0_BaseAddress + 0x102C))



extern void uart0_init(void);
extern void uart0_send(char c);
extern char uart0_recv(void);

extern void uputchar(char c);
extern char ugetchar(void);
extern void uputs(char *s);
extern char *ugets(char *s, int buf_len);
//extern int uprintf(const char *fmt, ...);

#endif

