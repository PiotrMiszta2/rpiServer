#include "client_handler.h"
#include "common.h"
#include "server.h"
#include "util.h"
#include "messages.h"

typedef struct ClientHandler_msg {
    int len;
    char buffer[CLIENT_HANDLER_BUFFER_MAX_LEN]; /* this should be converted into MessageS type*/
}ClientHandler_msg;

typedef struct ClientHandlerSignalS
{
    SignalS* signal;
    uint8_t id;
}ClientHandlerSignalS;

static inline void ClientHandler_read(ServerConnectionS* conn, ClientHandler_msg* msg);
static void ClientHandler_handle_msg(char* msg);
static void ClientHandler_write(ServerConnectionS* conn, ClientHandler_msg* msg);


/* <<< Function clientHandler_start_thread */
/**
 * @brief   Function is called when new client connect
 *          to the server only one thing what clientHandler
 *          must do, iis comunicating with client, and
 *          creating new threads for doing things for client.
 * @param arg pointer to ServerConnectionS cast to void*
 * @return NULL
 ***********************************************************/
void* clientHandler_start_thread(void* arg)
{
    uint8_t threadId = 0;
    if(arg)
    {
        //threadId = *(uint8_t*)(arg);
    }
    /* ** For debug ** */

    ClientHandler_msg* recvMsg = calloc(1, sizeof(ClientHandler_msg));
    ClientHandler_msg* writeMsg = calloc(1, sizeof(ClientHandler_msg));

    ServerConnectionS * conn = (ServerConnectionS *)arg;
    threadId = conn -> id;
    //TODO: (Piotr) end loop
    for(int i = 0;i < 100; i++)
    {
        /*  Reading, writing for debug and doing requst msg, its all */
        ClientHandler_read(conn, recvMsg);
        LOG_DEBUG("Server recaived msg from client: received a msg: Thread: %d, received msg %s", threadId, recvMsg->buffer);

        ClientHandler_handle_msg(recvMsg->buffer);
        const char buff[] = "Test debug";
        memcpy(writeMsg->buffer, buff, sizeof(buff));
        writeMsg->len = sizeof(buff);
        ClientHandler_write(conn, writeMsg);

/*        int* k = malloc(sizeof(int));
        *k = 5;
        SignalS* signal = common_signal_add_payload(k, sizeof(int));
        common_signal_send(5, signal);
*/
    }

    close(conn->sock);
    free(conn);
    pthread_exit(0);
}

void ClientHandler_read(ServerConnectionS* conn, ClientHandler_msg* msg)
{
    /* ****  Waiting for read msg and dont returning when reading thrash **** */
    while(1)
    {
        /* this must be stopped ;d maybe for  */
        read(conn->sock, &msg->len, sizeof(int));
        if (read(conn->sock, msg->buffer, msg->len) > 0)
            break;
    }
}
/**
 * @brief   Function ClientHandler_handle_msg
 *          is used to parsed msg - extract payload from msg
 *          and executing client request
 * @param msg - message from client
 */
void ClientHandler_handle_msg(char *msg)
{
    MessageS* toSwitch =  message_create_from_char(msg);
    /* now check type */
    MessageTypeE type = message_get_type(toSwitch);
    switch (type)
    {
    case MESSAGE_TYPE_REQ:
        /* IF GET REQUEST NEED TO SEND SIGNAL TO SERIAL THREAD
            TO RESOLVE THIS REQUEST, WAIT FOR SIGNAL FROM SERIAL THREAD
            THAT REQUEST CAN BE CONFIRMED OR REJECTED */
        printf("get request\n");
        MessageMicroReqS* payload = message_get_payload(toSwitch);
        SignalS* signal = common_signal_add_payload(payload, sizeof(MessageMicroReqS));
        /* STM 32 is first micro controler, but we need to send to thread number = offset + payload.micro */
        common_signal_send(COMMON_THREADS_SERIAL_THREAD_OFFSET + payload->micro, signal);
        break;
    /*TODO: create pretty logger options to signals recaived */
    case MESSAGE_TYPE_REJ:
        printf("get rej\n");
        /* THIS SHOULD NEVER BE USED */
        break;
    case MESSAGE_TYPE_CFM:
        printf("get cfm\n");
        /* THIS SHOULD NEVER BE USED */
        break;
    default:
        printf("get nothing\n");
        /* THIS SHOULD NEVER BE USED */
        break;
    }
    /*TODO: need to free allocated memory, like toSwitch*/
    free(toSwitch);
}

static void ClientHandler_write(ServerConnectionS* conn, ClientHandler_msg* msg)
{
    write(conn->sock, &msg->len, sizeof(msg->len));
    write(conn->sock, msg->buffer, msg->len);
}
