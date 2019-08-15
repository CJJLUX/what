#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#define right   10000
#define left    10200

int main()
{
    int i, j;
    int mark;
    pid_t pid;

    for (i = right; i <= left; i++) {
        pid = fork();
        if (pid < 0) {
            goto fork_err;
        }
        else if (pid == 0) { 
            mark = 1;
            for (j = 2; j < i/2; j++)
            {
                if (i % j == 0) {
                    mark = 0;
                    break;
                }
            
            }
            if ( 1 == mark )
                printf("this is a %d\n", i);
            exit(0);
        }
    int st;
    for (i = right; i <= left; i++)
          wait(NULL);
        //wair_pid();
    }
    exit(0);
fork_err:
    printf("fork_err()\n");
    return -1;

}


