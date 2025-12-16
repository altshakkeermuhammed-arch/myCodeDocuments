#include "shared.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, sizeof(shm_queue_t));

    shm_queue_t *q = mmap(NULL, sizeof(*q),
                          PROT_READ | PROT_WRITE,
                          MAP_SHARED, fd, 0);

    q->head = q->tail = q->count = 0;

    pthread_mutexattr_t mattr;
    pthread_condattr_t  cattr;

    pthread_mutexattr_init(&mattr);
    pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);

    pthread_condattr_init(&cattr);
    pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&q->mutex, &mattr);
    pthread_cond_init(&q->not_empty, &cattr);
    pthread_cond_init(&q->not_full, &cattr);

    printf("Shared memory initialized\n");
    return 0;
}
