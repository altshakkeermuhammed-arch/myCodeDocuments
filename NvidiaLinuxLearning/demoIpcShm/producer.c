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

    for (int i = 1; i <= 5; i++) {
        pthread_mutex_lock(&q->mutex);

        while (q->count == QUEUE_SIZE)
            pthread_cond_wait(&q->not_full, &q->mutex);

        q->buffer[q->tail] = i;
        q->tail = (q->tail + 1) % QUEUE_SIZE;
        q->count++;

        printf("Producer: produced %d\n", i);
        fflush(stdout);

        pthread_cond_signal(&q->not_empty);
        pthread_mutex_unlock(&q->mutex);

        sleep(1);
    }

    return 0;
}

