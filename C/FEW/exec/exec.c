#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *path = "/bin/date";

    puts("Begin!");//行缓存
    fflush(NULL);//之前的还没来的及缓冲出来就被execl打断了
    //所以需要fflush去刷新全缓存
    execl(path, "data", "+%s", NULL);//会替换以前的那个进程，但是pid不变
    perror("execl()");////////只要不出错，下面就不执行了
    exit(1);

    puts("End!");
    
    exit(0);
}

