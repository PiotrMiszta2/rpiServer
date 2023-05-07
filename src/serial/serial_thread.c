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
#include "serial_thread.h"
#include "serial_signal.h"
#include "common.h"

/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
void* serial_thread_start(void* arg)
{
    /* TODO: arg need to have id of thread */
    uint8_t threadId = (*(uint8_t*)(arg));

    while(1)
    {
        /* check signal and handle it */
        if(serial_signal_check_signal(5))
        {
            LOG_INFO("Signal is waiting in queue\n");
            SignalS* signal = serial_signal_get(5);
            serial_signal_handler(signal);
        }
    }
    /* here thread will end*/
}

void serial_signal_handler(SignalS* signal)
{
    LOG_DEBUG("Handling signal");

}

/* Static Function Definitions ****************************************************************************************/