#ifndef RASPBERRY_MESSAGES_MICRO_REQ_H
#define RASPBERRY_MESSAGES_MICRO_REQ_H
/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file    messages_micro_req.h
 * @brief   file specify format of request action from microconroler: stm32 or arduino in our case
 *
 **********************************************************************************************************************/


/* INCLUDES ***********************************************************************************************************/
#include "util.h"
#include "common.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
/* struct for payload in msg */
typedef struct MessageMicroReq
{
    uint16_t request;
    uint8_t micro;
    uint8_t _padded;
}MessageMicroReq;
//for all messages type need to static_assert padding
static_assert(  sizeof(MessageMicroReq) ==  \
                sizeof(uint16_t) + sizeof(uint8_t) * 2,
                "MessageMicroReq padded");
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/

#endif //RASPBERRY_MESSAGES_REQ_MICRO_H
