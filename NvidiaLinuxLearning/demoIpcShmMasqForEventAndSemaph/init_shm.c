#include "ipc_common.h"

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(shm_queue_t));

    shm_queue_t *q = mmap(NULL, sizeof(*q),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, 0);

    /* Initialize shared data */
    q->head = q->tail = q->count = 0;

    /* Initialize process-shared semaphore */
    sem_init(&q->mutex, 1, 1);   // pshared=1, initial value=1

    /* Create message queues */
    struct mq_attr attr = {
        .mq_flags = 0,
        .mq_maxmsg = 10,
        .mq_msgsize = sizeof(int),
        .mq_curmsgs = 0
    };

    mq_open(MQ_NOT_EMPTY, O_CREAT, 0666, &attr);
    mq_open(MQ_NOT_FULL,  O_CREAT, 0666, &attr);

    printf("Shared memory, semaphore, and message queues initialized\n");
    return 0;
}

