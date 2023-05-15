#include "serial_signal.h"
#include "queue.h"
#include "logger.h"
#include "common_thread.h"
#include <assert.h>
#include <pthread.h>

#define SERIAL_SIGNAL_MAX_THREADS   2

static Queue** signal_que;
static pthread_mutex_t* mutex;
static sem_t* queEmpty;
static sem_t* queFull;

static inline uint8_t getId(uint8_t id)
{
    return id - COMMON_THREADS_SERIAL_THREAD_OFFSET;
}

static inline void serial_signal_free_queue(void* arg)
{
    SignalS* sig = (SignalS*)(arg);
    common_signal_free(sig);
}

void serial_signal_init(void) //each id shoud have own que
{
    signal_que = malloc(queue_sizeof() * SERIAL_SIGNAL_MAX_THREADS);
    queEmpty = malloc(sizeof(sem_t) * SERIAL_SIGNAL_MAX_THREADS);
    queFull = malloc(sizeof(sem_t) * SERIAL_SIGNAL_MAX_THREADS);
    mutex = malloc(sizeof(pthread_mutex_t) * SERIAL_SIGNAL_MAX_THREADS);
    assert(queEmpty);
    assert(queFull);
    assert(mutex);
    assert(signal_que);
    for(size_t i = 0; i < SERIAL_SIGNAL_MAX_THREADS; i++)
    {
        pthread_mutex_init(&mutex[i], NULL);
        sem_init(&queEmpty[i], 0, 10);
        sem_init(&queFull[i], 0, 0);
        signal_que[i] = queue_create(serial_signal_free_queue);
    }
}

void serial_signal_add_to_queue(SignalS* signal, uint8_t _id)
{
    uint8_t id = getId(_id);
    sem_wait(&queEmpty[id]);
    pthread_mutex_lock(&mutex[id]);
    queue_push_back(signal_que[id], (void*)(signal));
    pthread_mutex_unlock(&mutex[id]);
    sem_post(&queFull[id]);
}

int serial_signal_check_signal(uint8_t _id)
{
    uint8_t id = getId(_id);
    pthread_mutex_lock(&mutex[id]);
    if(queue_empty(signal_que[id]))
    {
        pthread_mutex_unlock(&mutex[id]);
        return 0;
    }
    else
    {
        pthread_mutex_unlock(&mutex[id]);
        return 1;
    }

}
SignalS* serial_signal_get(uint8_t _id)
{
    uint8_t id = getId(_id);
    sem_wait(&queFull[id]);
    pthread_mutex_lock(&mutex[id]);
    SignalS* sig = queue_pop(signal_que[id]);
    pthread_mutex_unlock(&mutex[id]);
    sem_post(&queEmpty[id]);
    return sig;
}

void serial_signal_destroy(void)
{
    for(size_t i = 0 ; i < SERIAL_SIGNAL_MAX_THREADS; i++)
    {
        queue_destroy(signal_que[i]);
    }
    free(signal_que);
}
