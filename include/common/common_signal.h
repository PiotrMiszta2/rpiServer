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
#include <stdint.h>
#include <assert.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct SignalS SignalS;
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
SignalS* common_signal_add_payload(void* payload, size_t size);
void* common_signal_get_payload(SignalS* signal);
void common_signal_send(uint8_t id, SignalS* payload);
#endif //RASPBERRY_COMMON_TYPES_H