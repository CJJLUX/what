#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define path    "/bin/date"

int main()
{
    pid_t pid;
    puts("------Start");
    fflush(NULL);

    pid = fork();
    if (pid < 0) {
        goto fork_err;
    }
    else if (pid == 0) {
        execl(path, "date", "+%s", NULL);
        perror("execl()");
        exit(1);
    }
    wait(NULL);

    puts("------End");

    exit(0);
fork_err:
    perror("fork()");
    exit(1);
}

