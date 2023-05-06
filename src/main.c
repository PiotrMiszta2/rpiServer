#include "server.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include "common_signal.h"
#include "common_thread.h"
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
    pthread_t thread;
    logger_init("log.log");
    common_thread_init();
    common_thread_create(&thread, NULL, start_dummy_thread, NULL, 6);
    server_start();
    server_listen();
    logger_close();
    pthread_join(thread, NULL);
    return 0;
}
