#ifndef RASPBERRY_COMMON_TYPES_H
#define RASPBERRY_COMMON_TYPES_H


#include <stdlib.h>
#include <assert.h>
#include "common_signal.h"

typedef struct CommonSignalToMicroS
{
    SignalS* signal;
    uint8_t thread;
}CommonSignalToMicroS;

CommonSignalToMicroS* common_signal_to_micro_create(SignalS* signal, uint8_t thread);

#endif //RASPBERRY_COMMON_TYPES_H
