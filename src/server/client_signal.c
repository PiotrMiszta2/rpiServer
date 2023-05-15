#include "client_signal.h"
#include "util.h"
#include <pthread.h>

#define CLIENT_SIGNAL_MAX_THREADS   2

static Queue** signal_que;

static inline void client_signal_free_queue(void* arg)
{
    SignalS* sig = (SignalS*)(arg);
    common_signal_free(sig);
}

void client_signal_init(void) //each id shoud have own que
{
    signal_que = malloc(queue_sizeof() * CLIENT_SIGNAL_MAX_THREADS);
    for(size_t i = 0; i < CLIENT_SIGNAL_MAX_THREADS; i++)
    {
        signal_que[i] = queue_create(client_signal_free_queue);
    }
}

void client_signal_add_to_queue(SignalS* signal, uint8_t id)
{
    queue_push_back(signal_que[id - COMMON_THREADS_CLIENT_THREAD_OFFSET], (void*)(signal));
}

int client_signal_check_signal(uint8_t id)
{
    if(queue_empty(signal_que[id - COMMON_THREADS_CLIENT_THREAD_OFFSET]))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
SignalS* client_signal_get(uint8_t id)
{
    return queue_pop(signal_que[id - COMMON_THREADS_CLIENT_THREAD_OFFSET]);
}

void client_signal_handler(SignalS* signal)
{
    LOG_DEBUG("Handling signal: client thread");
    (void)signal;
}

void client_signal_destroy(void)
{
    for(size_t i = 0 ; i < CLIENT_SIGNAL_MAX_THREADS; i++)
    {
        queue_destroy(signal_que[i]);
    }
    free(signal_que);
}
