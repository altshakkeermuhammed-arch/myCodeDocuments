#include "shared.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int shm_fd = shm_open(SHM_NAME, O_RDWR, 0);
    shm_queue_t *q = mmap(NULL, sizeof(*q),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, shm_fd, 0);

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&q->mutex);

        while (q->count == 0)
            pthread_cond_wait(&q->not_empty, &q->mutex);

        int data = q->buffer[q->head];
        q->head = (q->head + 1) % QUEUE_SIZE;
        q->count--;

        printf("Consumer: consumed %d\n", data);
        fflush(stdout);

        pthread_cond_signal(&q->not_full);
        pthread_mutex_unlock(&q->mutex);

        sleep(2);
    }

    return 0;
}

