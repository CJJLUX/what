CFLAGS = -pthread
CC = gcc

#src := $(shell ls *.c)
#objs := $(patsubst %.c, %.o, src)
objs := test41.o

test: $(objs)
	$(CC) -o $@ $^ $(CFLAGS)
clean:
	rm -fr *.o test

