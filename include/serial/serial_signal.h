#ifndef RASPBERRY_SERIAL_SIGNAL_H
#define RASPBERRY_SERIAL_SIGNAL_H

#include <stdint.h>
#include "common.h"
/*  NOTE:   each file of existing component like serial client_handler
 *          need to have file *_signal.h and *_signal.c in this file
 *          need to have functions like
 *          init() - for initialize queue for signals
 *          add_to_queue() - for push incoming signal to que
 *          check_signal() - check that is any signal to handle
 *          signal_get() - to return first signal in que
 *
 *          For each thread must be another queue, so we can allocate at start
 *          queue for all threads, bcs its not much threds and queue have only 32 bites
 * */

/**
 * @brief init variables like que and mutex and semaphores
 *
*/
void serial_signal_init(void);
/**
 * @brief pushing to specify que by id signal
 *
*/
void serial_signal_add_to_queue(SignalS* signal, uint8_t id);
/**
 * @brief checking for signals in que specified by id
 *
*/
int serial_signal_check_signal(uint8_t id);
/**
 * @brief pop from que signal
*/
SignalS* serial_signal_get(uint8_t id);
void serial_signal_destroy(void);

#endif //RASPBERRY_SERIAL_SIGNAL_H
