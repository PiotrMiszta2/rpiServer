/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file
 * @brief
 *
 **********************************************************************************************************************/

/* INCLUDES ***********************************************************************************************************/
#include "client_handler.h"
#include "common_signal.h"
#include "server.h"
#include "util.h"
/* Type Declarations **************************************************************************************************/
typedef struct ClientHandler_msg {
    size_t len;
    char buffer[CLIENT_HANDLER_BUFFER_MAX_LEN];
}ClientHandler_msg;

typedef struct ClientHandlerSignalS
{
    SignalS* signal;
    uint8_t id;
}ClientHandlerSignalS;
/* Definitions ********************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/
static inline void ClientHandler_read(ServerConnectionS* conn, ClientHandler_msg* msg);
static void ClientHandler_handle_msg_request(char* msg);
static void ClientHandler_write(ServerConnectionS* conn, ClientHandler_msg* msg);
static void ClientHandler_parse_msg(char* msg);
/* Global Function Definitions ****************************************************************************************/


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
        LOG_DEBUG("Server recaived msg from client: received a msg: Thread: %d, received msg %s", threadId, recvMsg);

       ClientHandler_handle_msg_request(recvMsg->buffer);
       const char buff[] = "Test debug";
        memcpy(writeMsg->buffer, buff, sizeof(buff));
        writeMsg->len = sizeof(buff);
        ClientHandler_write(conn, writeMsg);

        int* k = malloc(sizeof(int));
        *k = 5;
        SignalS* signal = common_signal_add_payload(k, sizeof(int));
        common_signal_send(5, signal);
    }

    close(conn->sock);
    free(conn);
    pthread_exit(0);
}

/* Static Function Definitions ****************************************************************************************/
void ClientHandler_read(ServerConnectionS* conn, ClientHandler_msg* msg)
{
    /* ****  Waiting for read msg and dont returning when reading thrash **** */
    while(1)
    {
        read(conn->sock, &msg->len, sizeof(int));
        if (read(conn->sock, msg->buffer, msg->len) > 0)
            break;
    }

}
/**
 * @brief   Function ClientHandler_handle_msg_request
 *          is used to parsed msg - extract payload from msg
 *          and executing client request
 * @param msg - message from client
 */
void ClientHandler_handle_msg_request(char* msg)
{
    ClientHandler_parse_msg(msg);
}

void ClientHandler_parse_msg(char* msg)
{
    char temp[] = "Testowy message";
    if (strcmp(msg, temp) == 0)
        printf("OK\n");
}

static void ClientHandler_write(ServerConnectionS* conn, ClientHandler_msg* msg)
{
    write(conn->sock, &msg->len, sizeof(msg->len));
    write(conn->sock, msg->buffer, msg->len);
}
