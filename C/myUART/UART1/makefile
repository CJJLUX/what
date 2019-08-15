ARCH=arm
CC=$(ARCH)-linux-gcc
LD=$(ARCH)-linux-ld
OBJCOPY=$(ARCH)-linux-objcopy
uart.bin:start.s main.c uart.c
	$(CC) -g -c start.s main.c uart.c
	$(LD) -Ttext 0x0 -g start.o main.o uart.o -o uart_elf
	$(OBJCOPY) -O binary -S uart_elf uart.bin
$(OBJE):uart.o main.o
	$(CC) $^ -o $@ 
clean:
	rm -rf *.o uart.bin uart_elf 

