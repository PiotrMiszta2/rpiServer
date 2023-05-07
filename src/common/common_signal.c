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
/* Static Function Definitions ****************************************************************************************/