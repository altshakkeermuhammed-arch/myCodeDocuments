#include "ipc_common.h"

int main() {
    int shmfd = shm_open(SHM_NAME, O_RDWR, 0666);
    shm_queue_t *q = mmap(NULL, sizeof(*q),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, shmfd, 0);

    mqd_t mq_not_empty = mq_open(MQ_NOT_EMPTY, O_RDONLY);
    mqd_t mq_not_full  = mq_open(MQ_NOT_FULL,  O_WRONLY);

    int msg, value;

    for (;;) {

        /* Wait until queue becomes NOT EMPTY */
        if (q->count == 0) {
            mq_receive(mq_not_empty, (char *)&msg, sizeof(msg), NULL);
        }

        sem_wait(&q->mutex);   /* 🔒 BEGIN atomic section */

        value = q->buffer[q->head];
        q->head = (q->head + 1) % QUEUE_SIZE;
        q->count--;

        printf("[Consumer] Consumed %d\n", value);

        sem_post(&q->mutex);   /* 🔓 END atomic section */

        /* Notify producer if queue was full */
        if (q->count == QUEUE_SIZE - 1) {
            msg = 1;
            mq_send(mq_not_full, (char *)&msg, sizeof(msg), 0);
        }

        sleep(1);
    }
}

