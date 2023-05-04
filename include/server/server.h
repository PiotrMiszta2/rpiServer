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
//FIXME: check this struct must be public: declared in header file or source file
/**
 * @struct  ThreadS
 * @brief   ThreadS is struct for handling thread
 *          and thread id which is equal to index in dll
 *          there is easiest way to identity which thread
 *          end own job and want to free memory
 */
typedef struct ThreadS {
    pthread_t thread;   //8
    size_t index;       //8
    /* no padded */
}ThreadS;
static_assert(sizeof(ThreadS) == (sizeof(pthread_t) + sizeof(size_t)), "Padding ThreadS");

typedef struct ServerS {
    struct sockaddr_in      address;        //16
    DoubleLinkedList*       threads;        //8
    int                     sock;           //4
    char                    padded__[4];    //4
}ServerS;                                   //32
static_assert(sizeof(ServerS) ==
    (sizeof(struct sockaddr_in) + sizeof(DoubleLinkedList*) + sizeof(int) + sizeof(char[4])), "Padding ServerS");

typedef struct ServerConnectionS{
    int sock;
    struct sockaddr address;
    socklen_t addr_len;
    size_t index;
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

#endif //RASPBERRY_SERVER_H
