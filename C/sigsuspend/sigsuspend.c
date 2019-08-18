#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//typedef void (*sighandler_t)(int)

void signal_handler(int signal_num)
{
    write(1, "!", 1);

}

int main()
{
    int i;
    int ret;
    sigset_t sig_set, oset, save_set;

    signal(SIGINT, signal_handler);
    sigemptyset(&sig_set);
    sigaddset(&sig_set, SIGINT);

    sigprocmask(SIG_UNBLOCK, &sig_set, &save_set); //保存开始的信号状态
    while(1) {
        ret = sigprocmask(SIG_BLOCK, &sig_set, NULL); //阻塞住你想要阻塞的信号，并设置你想要响应的信号，并返回旧的信号(不关心旧的信号置为NULL)
        if (ret < 0) {
            perror("sigprocmask()");
        }
        for(i = 0; i < 10; i++) {
            write(1, "*", 1);
            sleep(1);
        }

        write(1, "\n", 1);
        sigprocmask(SIG_SETMASK, &oset, NULL);
        //      sigprocmask(SIG_UNBLOCK, &sig_set, NULL);
        //      raise(SIGINT);
    }
    sigprocmask(SIG_SETMASK, &save_set, NULL);//还原开始的信号状态

    exit(0);
}

