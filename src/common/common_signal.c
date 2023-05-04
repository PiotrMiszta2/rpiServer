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