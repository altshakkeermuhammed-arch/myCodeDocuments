#include "ipc_common.h"

int main() {
    int shmfd = shm_open(SHM_NAME, O_RDWR, 0666);
    shm_queue_t *q = mmap(NULL, sizeof(*q),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, shmfd, 0);

    mqd_t mq_not_empty = mq_open(MQ_NOT_EMPTY, O_WRONLY);
    mqd_t mq_not_full  = mq_open(MQ_NOT_FULL,  O_RDONLY);

    int msg;

    for (int i = 1; i <= 5; i++) {

        /* Wait until queue becomes NOT FULL */
        if (q->count == QUEUE_SIZE) {
            mq_receive(mq_not_full, (char *)&msg, sizeof(msg), NULL);
        }

        sem_wait(&q->mutex);   /* 🔒 BEGIN atomic section */

        q->buffer[q->tail] = i;
        q->tail = (q->tail + 1) % QUEUE_SIZE;
        q->count++;

        printf("[Producer] Produced %d\n", i);

        sem_post(&q->mutex);   /* 🔓 END atomic section */

        /* Notify consumer if queue was empty */
        if (q->count == 1) {
            msg = 1;
            mq_send(mq_not_empty, (char *)&msg, sizeof(msg), 0);
        }

        sleep(1);
    }
    return 0;
}

