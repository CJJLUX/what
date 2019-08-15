#include "uart.h"
#include <stdio.h>
#include <stdlib.h>

void uart0_init(void)
{
    //关闭上拉功能
    GPIOD_PULLENB_DISABLE_DEFAULT |= (1 << 14) | (1 << 18);
    GPIOD_PULLENB &= ~((1 << 14) | (1 << 18));
    //设置复用，作为串口
    GPIODALTFN0 &= ~(3 << 28);
    GPIODALTFN0 |= (1 << 28);

    GPIODALTFN1 &= ~(3 << 4);
    GPIODALTFN1 |= (1 << 4);

    //word length 8 
    //PARITY MODE  0
    //INFRARED MODE 0 
    //NUMBER OF STOP BIT  1
    ULCON0 &= ~(3 << 0);
    ULCON0 |= (3 << 0);
    ULCON0 &= (~(1 << 2) | ~(1 << 5) | ~(1 << 6));
    //串口里面有一个DMA的功能，cpu内存里面有一段数据，cpu不想亲力亲为就会告诉DMA，那么DMA就会发送给串口，串口再发出去
    //轮寻
    UCON0 &= ~(5 << 0);
    UCON0 |= (5 << 0);
    //关闭fifo
    UFCON0 = 0;
    //关闭afc
    UMCON0 = 0;
    //115200 需要用公式计算一下
	//UARTCLKGEN0L
	//Base Address: 0xC000_0000
	//Address = Base Address + 0xA9004
	//CLKSRCSEL0 [4:2] pllx 
	//CLKDIV0 [12:5] Divider value = CLKDIV0 + 1
	//UARTCLKENB
	//0xC000A9000
	//CLKGENENB [2] enable
	//printf("UART0 pll is %#x\n", UARTCLKGEN0L);
	//printf("UART0 is enble %#x\n", CLKGENENB);
    UBRDIV0 = 26; 
    UFRACVAL0 = 2;
}

void uart0_send(char c)
{
    //send
    UTXH0 = c;
    while ((UTRSTAT0 & (1 << 1)) == 0);
}

char uart0_recv(void)
{
    //recv
    while ((UTRSTAT0 & (1 << 0)) == 0);
    return URXH0;
}

void uputchar(char c)
{
   uart0_send(c); 
}

char ugetchar(void)
{
	char c;
    c = uart0_recv();
	return c;

}
void uputs(char *s)
{
    while (*s) {
            uputchar(*s);
            if (*s == '\n') {
            uputchar('\r');
         }
         s++;
    }
}

char *ugets(char *s, int buf_len)
{
    int count = 0;
    char *save = s;
    char c;

    while ( (c = ugetchar) != '\r') {
        if (count > buf_len - 1) {// 因为还有一个尾零
                break;
            }
            *s++ = ugetchar();
            count++;
    }
    *s = '\0';
    uputchar('\r');
    uputchar('\n');
    return save;
}

//int uprintf(const char *fmt, ...)
//{
//    va_list ap;
//    char c;
//    char* s;
//
//    va_start(ap, fmt);
//    
//    while (*fmt) {
//        if (*fmt == '%') {
//            fmt++;
//            switch (*fmt) {
//                case 'c':
//                    c = va_arg(ap, int);
//                    uputchar(c);
//                    break;
//                case 'd':
//                    n = va_arg(ap, int);
//                    if (n < 0) {
//                        uputchar('-');
//                        n = -n;
//                    }
//                    itoa(n, buf);
//                    uputs(buf);
//                    break;
//                case 's':
//                    s = va_arg(ap, char *);
//                    uputs(s);
//                    break;
//                default:
//                    break;
//            }
//        }else{
//            c = ugetchar();
//            if (c == '\n') {
//                uputchar('\r');
//            }
//            
//        }
//        
//    }
//}


