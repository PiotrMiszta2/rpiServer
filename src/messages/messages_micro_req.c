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
static_assert(  sizeof(MessageMicroReqS) ==  \
                sizeof(uint16_t) + sizeof(uint8_t) * 2,
                "MessageMicroReqS padded");

MessageMicroReqS* message_micro_req_create(MessageMicroReqTypeE type, MessageMicroReqMicroTypeE microType)
{
    MessageMicroReqS* msg = calloc(1, sizeof(MessageMicroReqS));
    assert(msg);
    msg->micro = (uint8_t)(microType);
    msg->request = (uint16_t)(type);
    msg->confirm = MESSAGE_MICRO_REQ_CONFIRM_VALUE;
    return msg;
}
bool message_micro_req_check_value(MessageMicroReqS* msg)
{
    bool ret = false;
    if(msg->confirm == MESSAGE_MICRO_CFM_CONFIRM_VALUE)
    {
        ret = true;
    }
    return ret;
}
/* Static Function Definitions ****************************************************************************************/
