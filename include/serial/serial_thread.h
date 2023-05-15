#ifndef RASPBERRY_SERIAL_THREAD_H
#define RASPBERRY_SERIAL_THREAD_H

#include "common.h"
#include "util.h"
#include <stdint.h>

void* serial_thread_start(void* arg);
void serial_signal_handler(SignalS* signal);

#endif //RASPBERRY_SERIAL_THREAD_H
