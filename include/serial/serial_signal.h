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
#include "common_signal.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
void serial_signal_init(void);
void serial_signal_handler(SignalS* signal);
void serial_signal_add_to_queue(SignalS* signal, uint8_t id);
int serial_signal_check_signal(uint8_t id);
SignalS* serial_signal_get(uint8_t id);
#endif //RASPBERRY_SERIAL_SIGNAL_H
