#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define DEBUG

int main(int argc __attribute__((unusd)), char **argv)
{
   /*warning: unused variable 'mypid'*/ 
    
int mypid __attribute__((unusd)) = getpid();
#ifndef DEBUG
    printf("MY PID = %d\n", mypid);
#endif

    return 0;
}


