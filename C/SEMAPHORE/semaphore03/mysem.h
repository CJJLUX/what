#ifndef MYSEM_H__
#define MYSEM_H__

typedef void mysem_t;

mysem_t *mysem_init(int initval);

int mysem_add(mysem_t *sem, int initval);

int mysem_sub(mysem_t *sem, int initval);

int mysem_destory(mysem_t *sem);

#endif

