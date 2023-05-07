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
    MESSAGE_TYPE_NUL,
}MessageTypeE;

typedef struct MessageHeaderS MessageHeaderS;

typedef struct MessageS MessageS;

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
MessageS* message_create(MessageTypeE type, void* payload, size_t sizePayload);
MessageTypeE message_get_type(MessageS* msg);
void* message_get_payload(MessageS* msg);
size_t message_get_size_payload(MessageS* msg);
char* message_create_char(MessageS* msg);
MessageS* message_create_from_char(char* msg);
bool message_check(MessageS* msg);
void message_free(MessageS* msg);

#endif //RASPBERRY_MESSAGES_TYPES_H
