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
#include "messages.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Definitions ****************************************************************************************/
MessageMicroCfmS* message_micro_cfm_create(MessageMicroReqTypeE type, MessageMicroReqMicroTypeE microType)
{
    MessageMicroCfmS* message = calloc(1, sizeof(MessageMicroCfmS));
    assert(message);
    message->micro = (uint8_t)(microType);
    message->request = (uint16_t) type;
    message->confirm = MESSAGE_MICRO_CFM_CONFIRM_VALUE;
    return message;
}

bool message_micro_cfm_check_value(MessageMicroCfmS* msg)
{
    bool ret = false;
    if(msg->confirm == MESSAGE_MICRO_CFM_CONFIRM_VALUE)
    {
        ret = true;
    }
    return ret;
}
/* Static Function Definitions ****************************************************************************************/
