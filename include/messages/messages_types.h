#ifndef RASPBERRY_MESSAGES_TYPES_H
#define RASPBERRY_MESSAGES_TYPES_H
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
#include "util.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef enum MessageTypeE
{
    MESSAGE_TYPE_REQ,
    MESSAGE_TYPE_CFM,
    MESSAGE_TYPE_REJ,
}MessageTypeE;

typedef struct MessageHeaderS
{
    uint32_t payloadSize;
    uint8_t check;   //should be always 1, 0 for sending checking data
    uint8_t type;    //CAST MessageTypeE to uint8_t
    char ___padded[2];
}MessageHeaderS;
static_assert(  sizeof(MessageHeaderS) == \
                sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint8_t) + sizeof(char[2]),
                "MessageHeaderS padded");

typedef struct MessageS
{
    MessageHeaderS header;
    void* payload;
}MessageS;
static_assert(  sizeof(MessageS) == \
                sizeof(MessageHeaderS) + sizeof(void*),
                "MessageHeaderS padded");
/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/

#endif //RASPBERRY_MESSAGES_TYPES_H