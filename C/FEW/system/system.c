#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
    char *cmd = "date +%s";
//    int ret;
//
//    ret = system(cmd);
//    if (ret < 0) {
//        perror("system()");
//    }
//
    pid_t pid;

    pid = fork();
    if (pid < 0) {
        perror("fork()");
        exit(1);
    } 
    else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", cmd, NULL); 
        perror("execl()");
        exit(1);
    }
   wait(NULL); 

    exit(0);
}

