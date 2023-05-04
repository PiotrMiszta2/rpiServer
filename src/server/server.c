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
#include <assert.h>
/* Definitions ********************************************************************************************************/
#define SERVER_PORT         8080
#define SERVER_MAX_LISTEN   5

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/
static ServerS* serverS_p;

/* Static Function Declarations ***************************************************************************************/
static inline void server_socket(void);
static inline void server_bind(void);
static inline int server_dll_thread_cmp(void* restrict n, void* restrict m);
static inline void server_dll_thread_free(void* thr);
static void server_create_serverS(void);
static inline ThreadS* server_alloc_thread(void);
static inline ServerConnectionS* server_allocate_connection(void);
static int server_start_thread(ServerConnectionS* connectionS_p);

/* Global Function Definitions ****************************************************************************************/
void server_start(void)
{
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

void server_end_thread(size_t id)
{
    ThreadS* thread = dll_pop_index(serverS_p->threads, id);
    pthread_cancel(thread->thread);
    //TODO: (Piotr) this thread is want to end his job handle it
}
//todo: i think another function to pop thread who ends job from list
//todo: so thread when ending job increase semaphore and this function
//todo: looking which thread pushed this semaphore,


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
    if(
            bind(serverS_p->sock, (struct sockaddr*) (&serverS_p->address) , sizeof(serverS_p->address))
            < 0)
    {
        FERROR("Can't bind\n");
        LOG_ERROR("Can't bind socket\n");
        exit(SERVER_BIND_ERROR);
    }
}

int server_dll_thread_cmp(void* restrict n, void* restrict m)
{
    size_t arg1 = ((ThreadS*)(n))->index;
    size_t arg2 = ((ThreadS*)(m))->index;
    if(arg1 < arg2)
    {
        return -1;
    }
    else if(arg1 == arg2)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void server_dll_thread_free(void* thr)
{
    ThreadS* thread_p = (ThreadS *)(thr);
    pthread_cancel(thread_p->thread);
    free(thread_p);
}

void server_create_serverS(void)
{
    serverS_p = malloc(sizeof(ServerS));
    if(!serverS_p)
    {
        LOG_FATAL("serverS_p can't be allcated - aborted\n");
        FFATAL("serverS_p can't be allcated - aborted\n");
        assert(serverS_p); //NOT MUCH PROBABILITY
    }
    serverS_p->threads = dll_create(server_dll_thread_free, server_dll_thread_cmp);
    serverS_p->address.sin_family = AF_INET;
    serverS_p->address.sin_addr.s_addr = INADDR_ANY;
    serverS_p->address.sin_port = htons(SERVER_PORT);
}

ThreadS* server_alloc_thread(void)
{
    ThreadS* thread_p = malloc(sizeof(*thread_p));
    if(!thread_p)
    {
        FERROR("can't allocate memory for thread\n");
        LOG_ERROR("can't allocate memory for thread");
    }
    return thread_p;
}

ServerConnectionS* server_allocate_connection(void)
{
    ServerConnectionS* connectionS_p;
    connectionS_p = (ServerConnectionS *)malloc(sizeof(*connectionS_p));
    if(!connectionS_p)
    {
        LOG_ERROR("Can't allocate for connectionS_p");
        FERROR("Can't allocate for connectionS_p");
        assert(connectionS_p);
    }
    LOG_INFO("Allocating connection struct for incoming client");
    return connectionS_p;
}

int server_start_thread(ServerConnectionS* connectionS_p)
{
    //Allocating memory for pthread
    ThreadS* thread_p;
    if((thread_p = server_alloc_thread()) == NULL)
    {
        return -1;  //todo: error code
    }
    connectionS_p->index = dll_get_size(serverS_p->threads);
    //Starting new thread
    if (pthread_create(&(thread_p->thread),
                       NULL,
                       clientHandler_start_thread,
                       connectionS_p) != 0)
    {
        FERROR("Can't start thread\n");
        LOG_ERROR("Can't start thread for %d socket", connectionS_p->sock);
        free(thread_p);
        return -1; //todo: error code
    }
    else
    {
        //pushing new thread into que of threads
        thread_p->index = dll_get_size(serverS_p->threads);
        dll_push_back(serverS_p->threads, (void*)thread_p);
        LOG_INFO("Thread succesful created for new client");
        return 0;
    }
}


