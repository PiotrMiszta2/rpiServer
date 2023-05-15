#ifndef RASPBERRY_MESSAGES_MICRO_H
#define RASPBERRY_MESSAGES_MICRO_H

#include "util.h"
#include <assert.h>

#define MESSAGE_MICRO_REQ_CONFIRM_VALUE     (98)
#define MESSAGE_MICRO_REJ_CONFIRM_VALUE     (99)
#define MESSAGE_MICRO_CFM_CONFIRM_VALUE     (100)


typedef enum MessageMicroReqTypeE
{
    MESSAGE_MICRO_REQ_TYPE_LD1,
    MESSAGE_MICRO_REQ_TYPE_LD2,

}MessageMicroReqTypeE;

typedef enum MessageMicroReqMicroTypeE
{
    MESSAGE_MICRO_REQ_MICRO_TYPE_STM32,
    MESSAGE_MICRO_REQ_MICRO_TYPE_ARDUINO,
}MessageMicroReqMicroTypeE;

#endif //RASPBERRY_MESSAGES_MICRO_H
