#ifndef SHARED_H
#define SHARED_H

#include <pthread.h>

#define SHM_NAME "/demo_shm"
#define QUEUE_SIZE 5

typedef struct {
    int buffer[QUEUE_SIZE];
    int head;
    int tail;
    int count;

    pthread_mutex_t mutex;
    pthread_cond_t  not_empty;
    pthread_cond_t  not_full;
} shm_queue_t;

#endif

