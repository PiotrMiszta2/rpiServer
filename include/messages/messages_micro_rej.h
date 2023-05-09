#ifndef RASPBERRY_MESSAGES_MICRO_REJ_H
#define RASPBERRY_MESSAGES_MICRO_REJ_H
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
#include "messages_types.h"
#include "messages_micro.h"
#include <stdint.h>
#include <stdbool.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct MessageMicroRejS
{
    uint16_t request;
    uint8_t micro;
    uint8_t confirm;
}MessageMicroRejS;

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
MessageMicroRejS* message_micro_rej_create(MessageMicroReqTypeE type, MessageMicroReqMicroTypeE microType);
bool message_micro_rej_check_value(MessageMicroRejS* msg);
#endif //RASPBERRY_MESSAGES_MICRO_REJ_H