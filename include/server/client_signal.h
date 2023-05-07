#ifndef RASPBERRY_CLIENT_SIGNAL_H
#define RASPBERRY_CLIENT_SIGNAL_H
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
#include "common.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
void client_signal_init(void);
void client_signal_handler(SignalS* signal);
void client_signal_add_to_queue(SignalS* signal, uint8_t id);
int client_signal_check_signal(uint8_t id);
SignalS* client_signal_get(uint8_t id);
void client_signal_destroy(void);
#endif //RASPBERRY_CLIENT_SIGNAL_H