#ifndef RASPBERRY_COMMON_THREAD_H
#define RASPBERRY_COMMON_THREAD_H

#include <pthread.h>
#include <stdint.h>

#define COMMON_THREADS_CLIENT_THREAD_OFFSET     10
#define COMMON_THREADS_SERIAL_THREAD_OFFSET     5

void common_thread_init(void);
int common_thread_create(   pthread_t *restrict thread,
                            const pthread_attr_t *restrict attr,
                            void*(*start_runtine)(void *),
                            void *restrict arg,
                            const uint8_t id ); //this should be stored in queue
int common_thread_check(uint8_t id);

#endif //RASPBERRY_COMMON_THREAD_H
