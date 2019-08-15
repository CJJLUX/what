#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
#include <sys/time.h>
#include <semaphore.h>  
#include <errno.h>  
#include <string.h>


#define handle_error(msg) \
	do { perror(msg); return -1; } while (0)

struct PrivInfo  
{  
	sem_t s1;  
	sem_t s2;  
	unsigned int sem_timeout;
	unsigned int sem_flag;
};  

static struct timespec t;


void time_add_ms(struct timeval *time, unsigned int ms)
{
	time->tv_usec += ms * 1000; 
	if(time->tv_usec >= 1000000) 
	{
		time->tv_sec += time->tv_usec / 1000000;
		time->tv_usec %= 1000000;
	}
}


void time_out_init(unsigned int time_ms)
{
	struct timeval time;

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	gettimeofday(&time, NULL);
	time_add_ms(&time, time_ms);
	t.tv_sec = time.tv_sec;
	t.tv_nsec = time.tv_usec * 1000;
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

struct PrivInfo *mysem_init(struct PrivInfo *thiz, unsigned int sem_val,
		    					unsigned int sem_flag, unsigned int sem_timeout)  
{  
    struct PrivInfo *mythiz;

    mythiz = (struct PrivInfo *)malloc(sizeof(*thiz));  
    if (mythiz == NULL) {  
        return NULL;  
    } 

    memset(mythiz, 0, sizeof(*thiz));
    mythiz->sem_timeout = sem_timeout;
    mythiz->sem_flag	= sem_flag;

    if (sem_init(&mythiz->s1, 0, 0) < 0) {
        return NULL;  
    }  
    if (sem_init(&mythiz->s2, 0, sem_val) < 0) {
        return NULL;  
    }  

	
    return mythiz;  
}  

int mysem_destroy(struct PrivInfo *thiz)  
{  
    if (sem_destroy(&thiz->s1) < 0) {
        handle_error("info_destroy");
    }  

    if (sem_destroy(&thiz->s2) < 0) {
        handle_error("info_destroy");
    }  	

    free(thiz);  
    thiz = NULL;  

    return 0;  
}  

void mysem_wait(struct PrivInfo *thiz) 
{
    int semvalue = -1;
    int ret = -1;

    sem_getvalue(&thiz->s1, &semvalue);
    printf("will call sem_timedwait, semvalue = %d\n", semvalue);

    if (thiz->sem_flag) {
        printf("------start time_out------\n");
        time_out_init(thiz->sem_timeout);
        ret = sem_timedwait(&thiz->s2, &t);
        if (ret < 0) {
            printf("////////sem_timedwait-outtime//////\n");
            pthread_exit(NULL);
        }
    } else {
        sem_wait(&thiz->s2);  
    }

    sem_post(&thiz->s1);  
    printf("pthread1: pthread1 unlock\n");  
}

void mysem_post(struct PrivInfo *thiz)
{
    int semvalue = -1;

    sem_getvalue(&thiz->s1, &semvalue);
    printf("will call sem_timedwait, semvalue = %d\n", semvalue);

    if (thiz->sem_flag) {
        printf("------start time_out------\n");
        time_out_init(thiz->sem_timeout);
        ret = sem_timedwait(&thiz->s1, &t);
        if (ret < 0) {
            printf("////////sem_timedwait-outtime//////\n");
            pthread_exit(NULL);
        }
    } else {
        sem_wait(&thiz->s1);  
    }
    printf("pthread2: pthread2 get the unlock.\n");  

    sem_post(&thiz->s2);  
}

static void *pthread_func_1(struct PrivInfo *thiz)  
{  
    int times_count = 0;

    printf("pthread1\n");
    printf("***************sem_timeout = %d****\n", thiz->sem_timeout);
    while(1) {
        mysem_post(thiz);
        times_count++;
        printf("pthread1: pthread1 get the lock. times_count = %d\n", times_count);  
        sleep(1);
    }
}  

static void *pthread_func_2 (struct PrivInfo *thiz)  
{  
    int semvalue = -1;

    printf("pthread2\n"); 
    while(1) {
        mysem_wait(thiz);
        printf("pthread2: pthread2 unlock.\n");  
        sleep(1);
    }
}

int main (int argc, char **argv)  
{  
    pthread_t pt_1 = 0;  
    pthread_t pt_2 = 0;  
    int ret = 0;  
    int myval = -1;
    struct PrivInfo *thiz = NULL;  

    if(argc > 0) {
        myval = atoi(argv[1]);
    }

    thiz = mysem_init(thiz, myval, 1, 10000);  
    if (thiz == NULL) {
        handle_error("mysem_init()");
    }
	
	ret = pthread_create(&pt_1, NULL, (void *)pthread_func_1, thiz);  
	if (ret != 0) {  
			handle_error("pthread_1_create:");
	}  
	ret = pthread_create(&pt_2, NULL, (void *)pthread_func_2, thiz);  
	if (ret != 0) {  
			handle_error("pthread_2_create:");
	}  

	pthread_join(pt_1, NULL);  
	pthread_join(pt_2, NULL);  

	mysem_destroy(thiz);  

	return 0;  
}  

