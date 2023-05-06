#include "server.h"
#include "logger.h"
#include <stdlib.h>
#include <string.h>
#include "common_signal.h"
#include "common_thread.h"

int main(void)
{
    logger_init("log.log");
    /*ParserMsgS* msg = messages_request_micro_create(1, 10);
    messages_request_micro_handle(msg);
    parser_msg_delete(msg);*/
    common_thread_init();
    server_start();
    server_listen();
    logger_close();
    return 0;
}
