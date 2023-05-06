/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file
 * @brief
 *
 **********************************************************************************************************************/

/* INCLUDES ***********************************************************************************************************/
#include "serial_signal.h"
#include "queue.h"
#include "logger.h"
#include "common_thread.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/
#define SERIAL_SIGNAL_MAX_THREADS   2
/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/
static Queue** signal_que;
/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
void serial_signal_init(void) //each id shoud have own que
{
    signal_que = malloc(queue_sizeof() * SERIAL_SIGNAL_MAX_THREADS);
    for(size_t i = 0; i < SERIAL_SIGNAL_MAX_THREADS; i++)
    {
        signal_que[i] = queue_create(NULL);
    }
}

void serial_signal_add_to_queue(SignalS* signal, uint8_t id)
{
    queue_push_back(signal_que[id - COMMON_THREADS_SERIAL_THREAD_OFFSET], (void*)(signal));
}

int serial_signal_check_signal(uint8_t id)
{
    if(queue_empty(signal_que[id - COMMON_THREADS_SERIAL_THREAD_OFFSET]))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
SignalS* serial_signal_get(uint8_t id)
{
    return queue_pop(signal_que[id - COMMON_THREADS_SERIAL_THREAD_OFFSET]);
}

void serial_signal_handler(SignalS* signal)
{
    LOG_DEBUG("Handling signal");

}
/* Static Function Definitions ****************************************************************************************/



