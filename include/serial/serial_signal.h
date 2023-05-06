#ifndef RASPBERRY_SERIAL_SIGNAL_H
#define RASPBERRY_SERIAL_SIGNAL_H
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
#include <stdint.h>
#include "common.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
/*  NOTE:   each file of existing component like serial client_handler
 *          need to have file *_signal.h and *_signal.c in this file
 *          need to have functions like
 *          init() - for initialize queue for signals
 *          add_to_queue() - for push incoming signal to que
 *          check_signal() - check that is any signal to handle
 *          signal_get() - to return first signal in que
 *
 *          For each thread must be another queue, so we can allocate at start
 *          queue for all threads, bcs its not much threds and queue have only 32 bites
 * */


void serial_signal_init(void);
void serial_signal_add_to_queue(SignalS* signal, uint8_t id);
int serial_signal_check_signal(uint8_t id);
SignalS* serial_signal_get(uint8_t id);
void serial_signal_destroy(void);
#endif //RASPBERRY_SERIAL_SIGNAL_H
