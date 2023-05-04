#ifndef RASPBERRY_CLIENTHANDLER_H
#define RASPBERRY_CLIENTHANDLER_H
/**
 * Copyright
 **********************************************************************************************************************/
/**
 *
 *
 * @file ClientHandler.h
 * @brief Header file for interface between Client and Server
 *
 **********************************************************************************************************************/


/* INCLUDES ***********************************************************************************************************/
#include <string.h>
#include "server_defs.h"
/* Definitions ********************************************************************************************************/
/**
 * @def CLIENT_HANDLER_BUFFER_MAX_LEN
 * @brief max len of msg sending by client
 */

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/

/* Global Function Declarations ***************************************************************************************/
/**
 * @brief   function clientHandler_start_thread
 *          starting thread after client connect to server
 * @return NULL
 */
void* clientHandler_start_thread(void* arg);

#endif //RASPBERRY_CLIENTHANDLER_H

