#ifndef RASPBERRY_SERVER_H
#define RASPBERRY_SERVER_H
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
#include <sys/socket.h>
#include <stdlib.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <assert.h>

#include "double_linked_list.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/
typedef struct ServerS {
    struct sockaddr_in      address;        //16
    int                     sock;           //4
    char                    padded__[12];    //4
}ServerS;                                   //24
static_assert(sizeof(ServerS) ==
    (sizeof(struct sockaddr_in) + sizeof(DoubleLinkedList*) + sizeof(int) + sizeof(char[4])), "Padding ServerS");

typedef struct ServerConnectionS{
    int sock;
    struct sockaddr address;
    socklen_t addr_len;
}ServerConnectionS;
static_assert(sizeof(ServerConnectionS) ==
    (sizeof(int) + sizeof(struct sockaddr) + sizeof(socklen_t) + sizeof(size_t)), "Padding ServerConnectionS");

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
/**
 * @brief   server_start allocating memory for data needs to create server
 *          and binding socket to port
*/
void server_start(void);

/**
 * @brief   listing for incominng connection and starting new thread
 *          with new connection
*/
void server_listen(void);

/**
 * @brief   search and end thread with no connection
 *
*/
//        TODO: not implemented yet
void server_end_thread(size_t id);
void server_wait_for_threads(void);
#endif //RASPBERRY_SERVER_H
