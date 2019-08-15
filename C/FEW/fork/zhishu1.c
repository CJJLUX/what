#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define right   10000
#define left    10200
#define NUM     3


int main()
{
    int i, j, n;
    int mark;
    pid_t pid;

    for (n = 0; n < NUM; n++) {
        pid = fork();
        if (pid < 0) {
            goto fork_err;
        }

        if (pid == 0) { 
            for (i = right + n; i <= left; i += NUM) {
                mark = 1;
                for (j = 2; j < i/2; j++) {
                    if (i % j == 0) {
                        mark = 0;
                        break;
                    }
                }
                if ( 1 == mark )
                    printf("[%d]this is a %d\n", n, i);
            }
            exit(0);
        }
    }
    for (n = 0; n < NUM; n++)
        wait(NULL);
    //wair_pid();

    exit(0);
fork_err:
    do {
        wait(NULL);
        printf("fork_err()\n");
    } while(n--);
    exit(1);
}


