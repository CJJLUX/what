#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
#include <sys/time.h>
#include <semaphore.h>  
#include <errno.h>  

typedef struct _PrivInfo  
{  
	sem_t s1;  
	sem_t s2;  
	unsigned int time_out;
}PrivInfo;  

struct timespec t;

#define TIME_OUT		
#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

// 时间 time 自加 ms 毫秒
void time_add_ms(struct timeval *time, uint ms)
{
	time->tv_usec += ms * 1000; // 微秒 = 毫秒 * 1000
	if(time->tv_usec >= 1000000) // 进位，1000 000 微秒 = 1 秒
	{
		time->tv_sec += time->tv_usec / 1000000;
		time->tv_usec %= 1000000;
	}
}


void time_out_init(unsigned int time_ms)
{
	struct timeval time;
	// 毫秒级别
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	gettimeofday(&time, NULL);
	time_add_ms(&time, time_ms);
	t.tv_sec = time.tv_sec;
	t.tv_nsec = time.tv_usec * 1000;
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

static int info_init(PrivInfo *mythiz, unsigned int sem_val, unsigned int time)  
{  
	PrivInfo *thiz = mythiz;

	thiz = malloc(sizeof(*thiz));
	if (thiz == NULL) {
		return -1;
	}
//	thiz->end_time = time(NULL) + 10;  
	sem_init(&thiz->s1, 0, 0);  
	sem_init(&thiz->s2, 0, sem_val);  
	thiz->time_out = time;		

	return 0;  
}  

static void info_destroy(PrivInfo *thiz)  
{  
	sem_destroy(&thiz->s1);  
	sem_destroy(&thiz->s2);  
	free(thiz);  
	thiz = NULL;  
	return;  
}  
void mysem_wait(PrivInfo *thiz) 
{
	int semvalue = -1;
	int ret = -1;

	printf("pthread1\n");  
//	sem_getvalue(&thiz->s1, &semvalue);
//	printf("will call sem_timedwait, semvalue = %d\n", semvalue);

#ifdef TIME_OUT
	printf("------start time_out------\n");
	time_out_init(thiz->time_out);
	ret = sem_timedwait(&thiz->s2, &t);
	if (ret < 0) {
		printf("////////sem_timedwait-outtime//////\n");
		//exit(1);
		pthread_exit(NULL);
	}
#else
			sem_wait(&thiz->s2);  
#endif
	sem_post(&thiz->s1);  
	printf("pthread1: pthread1 unlock\n");  
}

void mysem_post(PrivInfo *thiz)
{
	int semvalue = -1;
	int ret = -1;

	printf("pthread2\n");  
//	sem_getvalue(&thiz->s1, &semvalue);
//	printf("will call sem_timedwait, semvalue = %d\n", semvalue);

#ifdef TIME_OUT
	printf("------start time_out------\n");
	time_out_init(thiz->time_out);
	ret = sem_timedwait(&thiz->s1, &t);
	if (ret < 0) {
		printf("////////sem_timedwait-outtime//////\n");
		//exit(1);
		pthread_exit(NULL);
	}
#else
			sem_wait(&thiz->s1);  
#endif
	printf("pthread2: pthread2 get the unlock.\n");  

	sem_post(&thiz->s2);  
}

static void *pthread_func_1(PrivInfo *thiz)  
{  
	int time_count = 0;

	while(1) {
		mysem_post(thiz);
		time_count++;
		printf("pthread1: pthread1 get the lock. time_count = %d\n", time_count);  
		sleep(1);
	}
}  

static void *pthread_func_2 (PrivInfo *thiz)  
{  
	int semvalue = -1;

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
	PrivInfo *thiz = NULL;  

	if(argc > 0) {
		myval = atoi(argv[1]);
	} else {
		printf("please input the sem count\n");
		return -1;
	}

	ret = info_init(thiz, myval, 10000);  
	if (ret < 0) {
		return -1;
	}

	ret = pthread_create(&pt_1, NULL, (void *)pthread_func_1, thiz);  
	if (ret != 0)  
	{  
		perror ("pthread_1_create:");  
	}  
	ret = pthread_create(&pt_2, NULL, (void *)pthread_func_2, thiz);  
	if (ret != 0)  
	{  
		perror ("pthread_2_create:");  
	}  

	pthread_join(pt_1, NULL);  
	pthread_join(pt_2, NULL);  

	info_destroy(thiz);  

	return 0;  
}  

