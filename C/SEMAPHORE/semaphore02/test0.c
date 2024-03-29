#include <stdlib.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <pthread.h>  
#include <semaphore.h>  
#include <errno.h>  

typedef struct _PrivInfo  
{  
	sem_t s1;  
	sem_t s2;  
	time_t end_time;  
}PrivInfo;  

static void info_init(PrivInfo *thiz)  
{  
	thiz->end_time = time(NULL) + 10;  
	sem_init(&thiz->s1, 0, 1);  
	sem_init(&thiz->s2, 0, 0);  
	return;  
}  

static void info_destroy(PrivInfo *thiz)  
{  
	sem_destroy(&thiz->s1);  
	sem_destroy(&thiz->s2);  
	free(thiz);  
	thiz = NULL;  
	return;  
}  

static void *pthread_func_1(PrivInfo *thiz)  
{  
	printf("pthread1\n");  
	while (time(NULL) < thiz->end_time)  
	{  
		sem_wait(&thiz->s2);  
		printf("pthread1: pthread1 get the lock.\n");  
		sem_post(&thiz->s1);  
		printf("pthread1: pthread1 unlock\n");  
		sleep(1);  
	}  
}  

static void *pthread_func_2 (PrivInfo *thiz)  
{  
	printf("pthread2\n");  
	while (time(NULL) < thiz->end_time)  
	{  
		sem_wait(&thiz->s1);  
		printf("pthread2: pthread2 get the unlock.\n");  
		sem_post(&thiz->s2);  
		printf("pthread2: pthread2 unlock.\n");  
		sleep(1);  
	}  
}

int main (int argc, char **argv)  
{  
	pthread_t pt_1 = 0;  
	pthread_t pt_2 = 0;  
	int ret = 0;  
	PrivInfo *thiz = NULL;  
	thiz = (PrivInfo *)malloc(sizeof(PrivInfo));  
	if (thiz == NULL)  
	{  
		return -1;  
	}  

	info_init (thiz);  

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

