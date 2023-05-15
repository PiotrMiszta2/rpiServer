#ifndef RASPBERRY_MESSAGES_MICRO_REJ_H
#define RASPBERRY_MESSAGES_MICRO_REJ_H

#include "messages_types.h"
#include "messages_micro.h"
#include <stdint.h>
#include <stdbool.h>

#define message_create_micro_rej_create(msg)           ( message_create(MESSAGE_TYPE_REJ, msg, sizeof(MessageMicroRejS)) )
#define message_micro_rej_get_payload(msg)             ( (MessageMicroRejS*) (message_get_payload(msg)) )

typedef struct MessageMicroRejS
{
    uint16_t request;
    uint8_t micro;
    uint8_t confirm;
}MessageMicroRejS;

MessageMicroRejS* message_micro_rej_create(const MessageMicroReqTypeE type, const MessageMicroReqMicroTypeE microType);
bool message_micro_rej_check_value(const MessageMicroRejS* restrict msg);
void message_micro_rej_free(MessageMicroRejS* msg);
#endif //RASPBERRY_MESSAGES_MICRO_REJ_H