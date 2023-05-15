#ifndef RASPBERRY_COMMON_SIGNAL_H
#define RASPBERRY_COMMON_SIGNAL_H
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>

typedef struct SignalS SignalS;


SignalS* common_signal_add_payload(void* payload, size_t size);
void* common_signal_get_payload(SignalS* signal);
void common_signal_send(uint8_t id, SignalS* payload);
void common_signal_free(const SignalS* sig);

#endif //RASPBERRY_COMMON_TYPES_H
