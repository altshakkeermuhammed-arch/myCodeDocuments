#ifndef IPC_COMMON_H
#define IPC_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <mqueue.h>
#include <string.h>
#include <semaphore.h>

#define SHM_NAME "/demo_shm"
#define MQ_NOT_EMPTY "/mq_not_empty"
#define MQ_NOT_FULL  "/mq_not_full"

#define QUEUE_SIZE 5

typedef struct {
    sem_t mutex;                 /* NEW: protects shared memory */
    int buffer[QUEUE_SIZE];
    int head;
    int tail;
    int count;
} shm_queue_t;

#endif

