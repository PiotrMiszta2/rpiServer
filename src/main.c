#include "server.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include "serial_signal.h"
#include "common_signal.h"
#include "common_thread.h"
#include "serial_thread.h"
void init()
{
    logger_init("log.log");
    common_thread_init();
    serial_signal_init();
}

void* start_dummy_thread(void* arg)
{
    while(1)
    {
        printf("ok\n");
        sleep(2);
    }

}
int main(void)
{
    init();
    pthread_t thread;
    pthread_t serialThread;
    common_thread_create(&serialThread, NULL, serial_thread_start, NULL, 5);
    server_start();
    server_listen();
    logger_close();
    pthread_join(serialThread, NULL);
    return 0;
}
