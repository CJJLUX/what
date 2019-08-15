#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
////////////////IPC//////////////////
////////////////////////share-memory//////////////////

/*查一个文件里面有多少个a
 *打开一个文件
 *进行映射内存
 *创建两个进程
 *父进程向文件中写入100个a
 *子进程从文件读出100个a
 *并且子进程再去把这里的内容提取出来
 *然后去循环找出a
 */

//#define PATH    "/tmp/abc"

int main(int argc, char **argv)
{
    int len_count = -1;
    int pos = 0;
    int fd;
    int i;
    int ret = -1;
    int len = -1;
    struct stat statres;
    char *buf = NULL;
    pid_t pid;
    char father_buf[64] = "asasadsdsasadcadadadadcadadcsadvaadaa";
    char son_buf[64] = {0};

    if (argc < 0 || argc > 2) {
        fprintf(stderr, "argc error\n");
        exit(1);
    }

    fd = open(argv[1], O_CREAT | O_RDWR);
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

    /////////////////////////father-process////////////////////////////
    printf("father-process====\n");
    len_count = sizeof(father_buf);
    while (1) {
        len = write(fd, father_buf + len, len_count - pos);
        if (len < 0) {
            perror("write()");
        }
        pos += len; 
    }

    pid = fork();

    if (pid < 0) {
        perror("fork()");
    }
    /////////////////////////son-process//////////////////
    if (pid == 0) {
        printf("son-process====\n");
        while(buf != NULL) {
            int count = 0;
            for (i = 0; i < statres.st_size; i++) {
                if (buf[i] == 'a') {
                    count++;
                }
            }
            printf("%d=====\n", count);
        }
    }

 //   munmap(NULL, statres.st_size);
 //   wait(NULL);
 //   close(fd);

    exit(0);
}

