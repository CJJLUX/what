#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define func_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)


typedef struct my_sem {
	sem_t sem1;
	sem_t sem2;
} mysem;

static int sem_ret = 0;

int my_sem_init(mysem *sem)
{
	sem_ret = sem_init(&(sem->sem1), 0, 1);
	if (sem_ret < 0) {
		goto sem_init_err;
	}
	sem_ret = sem_init(&(sem->sem2), 0, 0);
	if (sem_ret < 0) {
		goto sem_init_err;
	}

	return 0;;
sem_init_err:
	exit(1);
}

int my_sem_distroy(mysem *sem)
{
	if (sem_destroy(&(sem->sem1)) < 0)
		goto sem_destroy_err;
	if (sem_destroy(&(sem->sem2)) < 0)	
		goto sem_destroy_err;

	return 0;
sem_destroy_err:
	exit(1);
}

static void *pthread_func1(mysem *sm)
{
    mysem *sem = (mysem *)sm; 
	sem_wait((&sem->sem1));
	printf("######pthread_func1######\n");
	sem_post((&sem->sem2));
	printf("########pthread_func1#####\n");
	pthread_exit(NULL);
}

static void *pthread_func2(mysem *sm)
{
    mysem *sem = (mysem *)sm; 
	sem_wait((&sem->sem2));
	printf("######pthread_func2######\n");
	sem_post((&sem->sem1));
	printf("######pthread_func2######\n");
	pthread_exit(NULL);
}

int main()
{
	int ret = 0;
	mysem *sem = NULL;
	pthread_t thead_id_1 = 0;
	pthread_t thead_id_2 = 0;

	sem = (mysem *)malloc(sizeof(mysem));
	if (sem == NULL) {
		func_error("malloc fail++++++");
	}

	my_sem_init(sem);

	ret = pthread_create(&thead_id_1, NULL, (void *)pthread_func1, sem);
	if (ret != 0) {
		func_error("pthread_create 1 is fail###########\n");
	}

	ret = pthread_create(&thead_id_2, NULL, (void *)pthread_func2, sem);
	if (ret != 0) {
		func_error("pthread_create 2 is fail###########\n");
	}

	my_sem_distroy(sem);

	pthread_join(thead_id_1, NULL);
	pthread_join(thead_id_2, NULL);

	exit(0);
}

