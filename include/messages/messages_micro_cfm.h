#ifndef RASPBERRY_MESSAGES_MICRO_CFM_H
#define RASPBERRY_MESSAGES_MICRO_CFM_H
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
typedef struct MessageMicroCfmS
{
    uint16_t request;
    uint8_t micro;
    uint8_t confirm;
}MessageMicroCfmS;
static_assert(sizeof(MessageMicroCfmS) ==       \
                sizeof(uint16_t) + sizeof(uint8_t) + sizeof(uint8_t),
                "MessageMicroCfmS padded");
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
MessageMicroCfmS* message_micro_cfm_create(MessageMicroReqTypeE type, MessageMicroReqMicroTypeE microType);
bool message_micro_cfm_check_value(MessageMicroCfmS* msg);
#endif //RASPBERRY_MESSAGES_MICRO_CFM_H