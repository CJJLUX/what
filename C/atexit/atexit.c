#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_frist(void)
{
    printf("my_frist()\n");
}

void my_secend()
{
    printf("my_secend()\n");
}

int main()
{
    atexit(my_secend);
    atexit(my_frist);

    exit(0);
 //   return 0;
//    _exit(0);
}

