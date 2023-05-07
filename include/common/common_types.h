#ifndef RASPBERRY_COMMON_TYPES_H
#define RASPBERRY_COMMON_TYPES_H
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
#include <stdlib.h>
#include <assert.h>
#include "common_signal.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct CommonSignalToMicroS
{
    SignalS* signal;
    uint8_t thread;
}CommonSignalToMicroS;
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
CommonSignalToMicroS* common_signal_to_micro_create(SignalS* signal, uint8_t thread);

#endif //RASPBERRY_COMMON_TYPES_H
