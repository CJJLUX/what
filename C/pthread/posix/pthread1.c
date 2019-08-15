#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

static void *func(void *p)
{
    printf("thread is working\n");
    pthread_exit(NULL);
}

int main()
{
    pthread_t tid;
    int err;

    puts("Begin");

    err = pthread_create(&tid, NULL, func, NULL);
    if (err) {
        fprintf(stderr, "pthread_create():%s\n", strerror(err));
    }

    pthread_join(tid, NULL);

    puts("end");

    exit(0);
}

