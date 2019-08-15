#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE     1024
typedef struct mycopy_t {
    int pos;
    int len;
    char buf[BUFSIZE];
} mycy;

int main()
{
    int sfd = -1;
    int bfd = -1;
    int ret = -1;
    mycy my;

    sfd = open("/tmp/mycopy", O_RDWR | O_NONBLOCK);
    if (sfd < 0) {
        perror("open()");
        exit(1);
    }
    bfd = open("/tmp/youcopy", O_RDWR | O_NONBLOCK);
    if (bfd < 0) {
        perror("open()");
        exit(1);
    }

    while (1) {
        my.len = read(sfd, my.buf, BUFSIZE);
        if (my.len < 0) {
            perror("read()");
            break;
        }

        if (my.len == 0) 
            break; 

        my.pos = 0;
        while (my.len > 0) {
            ret = write(bfd, my.buf + my.pos, my.len) ;
            if (ret < 0) {
                perror("write()");
                exit(1);
            }
            my.pos += ret;
            my.len -= ret;
        }
    }

    exit(0);
}

