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
#include "server.h"
#include "logger.h"
#include "client_handler.h"
#include "server_defs.h"
#include "common_thread.h"
#include <assert.h>
/* Definitions ********************************************************************************************************/
#define SERVER_PORT         8080
#define SERVER_MAX_LISTEN   5
#define SERVER_MAX_CLIENTS  3
/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/
static uint8_t numberOfClients;
static pthread_t client_thread[SERVER_MAX_CLIENTS];
/* Local Variable Definitions *****************************************************************************************/
static ServerS* serverS_p;

/* Static Function Declarations ***************************************************************************************/
static inline void server_socket(void);
static inline void server_bind(void);
static void server_create_serverS(void);
static inline ServerConnectionS* server_allocate_connection(void);
static int server_start_thread(ServerConnectionS* connectionS_p);

/* Global Function Definitions ****************************************************************************************/
void server_start(void)
{
    numberOfClients = 0;
    LOG_INFO("Server starting");
    //allocating memory for serverS
    server_create_serverS();
    // Create socket
    server_socket();
    // Bind socket
    server_bind();
    LOG_INFO("Server succesfull initializated, PORT: %d", SERVER_PORT);
}

void server_listen(void)
{
    LOG_INFO("Starting listen ...");
    if (listen(serverS_p->sock, SERVER_MAX_LISTEN) < 0)
    {
        LOG_ERROR("can't listen on port %d\n", SERVER_PORT);
        FERROR("Can't listen\n");
        exit(SERVER_LISTEN_ERROR);
    }
    ServerConnectionS* connectionS_p;
    //TODO: (piotr) endless loop when signal is detach SIGINT
    while (1)
    {
        //TODO: create semaphore that will be increment when thread will end job
        connectionS_p = server_allocate_connection();
        if(!connectionS_p)
        {
            return;
        }
        connectionS_p->sock = accept(serverS_p->sock, &connectionS_p->address, &connectionS_p->addr_len);
        if (connectionS_p->sock <= 0)
        {
            free(connectionS_p);
        }
        else
        {
            LOG_INFO("Connection accepted sock of new client = %d", connectionS_p->sock);
            if(server_start_thread(connectionS_p) != 0)
            {
                break;
            }
        }
    }
}
/* Static Function Definitions ****************************************************************************************/
void server_socket(void)
{
    serverS_p->sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverS_p->sock <= 0)
    {
        LOG_ERROR("can't create socket\n");
        FERROR("Can't create socket\n");
        assert(serverS_p->sock <= 0);
    }
}

void server_bind(void)
{
    if(bind(serverS_p->sock, (struct sockaddr*) (&serverS_p->address) , sizeof(serverS_p->address))
        < 0)
    {
        FERROR("Can't bind\n");
        LOG_ERROR("Can't bind socket\n");
        exit(SERVER_BIND_ERROR);
    }
}

void server_create_serverS(void)
{
    serverS_p = malloc(sizeof(ServerS));
    assert(serverS_p);
    serverS_p->address.sin_family = AF_INET;
    serverS_p->address.sin_addr.s_addr = INADDR_ANY;
    serverS_p->address.sin_port = htons(SERVER_PORT);
}


ServerConnectionS* server_allocate_connection(void)
{
    ServerConnectionS* connectionS_p;
    connectionS_p = (ServerConnectionS *)malloc(sizeof(*connectionS_p));
    assert(connectionS_p);
    LOG_INFO("Allocating connection struct for incoming client");
    return connectionS_p;
}

int server_start_thread(ServerConnectionS* connectionS_p)
{
    if (common_thread_create(&client_thread[numberOfClients],
                       NULL,
                       clientHandler_start_thread,
                       connectionS_p,
                       numberOfClients + COMMON_THREADS_CLIENT_THREAD_OFFSET) != 0)
    {
        FERROR("Can't start thread\n");
        LOG_ERROR("Can't start thread for %d socket", connectionS_p->sock);
        return -1; //todo: error code
    }
    else
    {
        LOG_INFO("Thread succesful created for new client");
        numberOfClients++;
        return 0;
    }
}


