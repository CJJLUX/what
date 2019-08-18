#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "mysem.h"


void *pthread_func0(void *sem)
{
    struct mysem_t *mysem0 = (struct mysem_t *)sem;
    
    printf("++++++++++++pthread_func0+++++\n");
    mysem_sub(mysem0, 2);

    pthread_exit(NULL);
}

void *pthread_func1(void *sem)
{
    struct mysem_t *mysem1 = (struct mysem_t *)sem;

    printf("++++++++++++pthread_func1+++++\n");
    mysem_sub(mysem1, 3);

    pthread_exit(NULL);
}

void *pthread_func2(void *sem)
{
    struct mysem_t *mysem2 = (struct mysem_t *)sem;
    int count = 0;
    int ret_val = -1;
    pthread_mutex_t mymut;

    //pthread_mutex_init(&mymut, NULL);
    while(1) {
        count++; 
        printf("++++++++++++pthread_func2+++++\n");

     //   pthread_mutex_lock(&mymut);
        ret_val = mysem_add(mysem2, 1);
        printf("+++++++++sem->value = %d++++++\n", ret_val);
       // pthread_mutex_unlock(&mymut);

        if ((count > 3) && (ret_val > 5)) {
            printf("-----------out-time----\n");
            pthread_exit(NULL); 
        }
    //    sleep(1);
    }

    pthread_exit(NULL); 
}

int main(int argc, char **argv)
{
    struct mysem_t *sem;
    pthread_t pth0 = 0;
    pthread_t pth1 = 0;
    pthread_t pth2 = 0;

    sem = mysem_init(0);
    pthread_create(&pth0, NULL, (void *)pthread_func0, sem);
    pthread_create(&pth1, NULL, (void *)pthread_func1, sem);
    pthread_create(&pth2, NULL, (void *)pthread_func2, sem);


    pthread_join(pth1, NULL);
    pthread_join(pth2, NULL);

    exit(0);
}


