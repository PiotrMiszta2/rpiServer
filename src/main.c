#include "server.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include "serial_signal.h"
#include "common_signal.h"
#include "common_thread.h"
#include "serial_thread.h"
#include "messages.h"
#include "queue.h"
#include "serial_tty.h"
static inline void init(void)
{
    logger_init("log.log");
    common_thread_init();
    serial_signal_init();
}
/* main thread = server thread */
int main(void)
{
    init();
    pthread_t serialThreadStm32;
    pthread_t serialThreadArduino;

    pthread_t serverThread;

    uint8_t stm32Id = 5;
    uint8_t arduinoId = 6;
    common_thread_create(&serialThreadStm32, NULL, serial_thread_start, &stm32Id, 5);
    common_thread_create(&serialThreadArduino, NULL, serial_thread_start, &arduinoId, 6);
    common_thread_create(&serverThread, NULL, server_thread, NULL, 1);

    pthread_join(serialThreadStm32, NULL);
    pthread_join(serialThreadArduino, NULL);
    pthread_join(serverThread, NULL);
    logger_close();
    return 0;
}
