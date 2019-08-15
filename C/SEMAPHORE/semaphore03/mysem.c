#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "mysem.h"

typedef struct{
    int value;
    pthread_mutex_t mut;
    pthread_cond_t cond;
}sem_t;

mysem_t *mysem_init(int initval)
{
    printf("=====start init======\n");
    sem_t *sem;

    sem = malloc(sizeof(*sem));
    if (sem == NULL) {
        goto malloc_error;
    }

    sem->value = initval;
    pthread_mutex_init(&sem->mut, NULL);
    pthread_cond_init(&sem->cond, NULL);

    return sem;
malloc_error:
    perror("malloc_error()");
    return NULL;
}

int mysem_add(mysem_t *the_sem, int initval)
{
    sem_t *sem = the_sem;

    printf("=====start add======\n");
    pthread_mutex_lock(&sem->mut);

    sem->value += initval;
    pthread_cond_signal(&sem->cond);

    printf("=====end add======\n");
    pthread_mutex_unlock(&sem->mut);

    return sem->value;
}

int mysem_sub(mysem_t *the_sem, int initval)
{
    sem_t *sem = the_sem;

    printf("=====start sub======\n");
    pthread_mutex_lock(&sem->mut);

	while(sem->value < initval) {
		pthread_mutex_unlock(&sem->mut);
		pthread_cond_wait(&sem->cond, &sem->mut); 
	}
    sem->value -= initval;

    printf("=====end sub======\n");
    pthread_mutex_unlock(&sem->mut);

    return sem->value;
}

int mysem_destroy(mysem_t *the_sem)
{
    sem_t *sem = the_sem;

    pthread_mutex_destroy(&sem->mut);
    pthread_cond_destroy(&sem->cond);
    free(sem);
    sem = NULL;

    return 0;
}

