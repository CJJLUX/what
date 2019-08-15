#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>

/*查一个文件里面有多少个a
 *打开一个文件
 *进行映射内存
 *再去把这里的内容提取出来
 *然后去循环找出a
 */

//#define PATH    "/tmp/abc"

int main(int argc, char **argv)
{
    int fd;
    int i;
    int ret = -1;
    struct stat statres;
    char *buf;

    if (argc < 0 || argc > 2) {
        fprintf(stderr, "argc error\n");
        exit(1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open()");
        return -1;
    }
    

    ret = fstat(fd, &statres); 
    if (ret < 0) {
        perror("fstat()");
        return -1;
    }

    buf = mmap(NULL, statres.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (buf == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    close(fd);

    int count = 0;
    for (i = 0; i < statres.st_size; i++) {
        if (buf[i] == 'a') {
            count++;
        }
    }
    printf("%d=====\n", count);

    munmap(NULL, statres.st_size);

    exit(0);
}

