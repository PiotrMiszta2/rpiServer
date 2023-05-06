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
#include "common_signal.h"
#include "common_thread.h"
#include "logger.h"
#include "serial_signal.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct SignalS
{
    void* data;
    size_t size;
}SignalS;
static_assert(sizeof(SignalS) == sizeof(void*) + sizeof(size_t), "SignalS padded");

/* Global Variable Definitions ****************************************************************************************/
/* Here we need to store signals */
/*  NOTE: One thread want to send signal to another so we need to know what threads are running
 *  and what type of signal they can store
 *  Now we need to communicate between client handler thread and serial thread so we need to know
 *  which thread is used to control stm32 whic is used to control arduino */
/*  TODO: specify command to run a thread so wrap pthread_create with function that will be
 *  returining thread by another argument will be info about thread like is stm32 thread
 **/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
SignalS* common_signal_add_payload(void* payload, size_t size)
{
    SignalS* signal = malloc(sizeof(SignalS));
    assert(signal);
    signal->data = payload;
    signal->size = size;
    return signal;
}
void* common_signal_get_payload(SignalS* signal)
{
    assert(signal);
    return signal->data;
}

void common_signal_send(uint8_t id, SignalS* payload)
{
    /* NOTE: need to send signal to thread
     * each module need to have handler for signal and queue for incoming signals
     * now we have only communicate between client_handlers threads and serial threads
     * but do this generic
     * //TODO: do signal handlling generic
     * */

    /* NOTE:    this function is call when we want to send payload to another thread
     *          we specify thread id, for example COMMON_THREADS_SERIAL_THREAD_OFFSET (5)
     *          so we want to signaling first of serial thread,
     *          if we have id of thread we need to call function in common_thread which should have
     *          this thread in table, check it that this thread exist
     * */
    if(common_thread_check(id) < 0)
    {
        LOG_ERROR("Thread %d dont exist, dont send signal, free payload\n", id);
        //TODO: check payload bcs maybe will be leak on data
        free(payload);
        return;
    }
    else
    {
        LOG_INFO("Sending signal to %d thread\n", id);
        /* NOTE:    switch wich function we want to call
         *          based on thread id but we need to
         *          check if threads are multiply instance
         *          so we need to push thread id and signal
         *          to specify queue
         * */
        if(id >= COMMON_THREADS_SERIAL_THREAD_OFFSET && id < COMMON_THREADS_CLIENT_THREAD_OFFSET)
        {
            LOG_DEBUG("call serial_signal_add_to_queue()");
            serial_signal_add_to_queue(payload, id);
        }
        else if (id >= COMMON_THREADS_CLIENT_THREAD_OFFSET && id < COMMON_THREADS_CLIENT_THREAD_OFFSET + 5)
        {
            //client_handler_signal_add_to_queue(payload, id);
        }
        return;
    }

}
/* Static Function Definitions ****************************************************************************************/