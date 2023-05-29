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
#include "serial_thread.h"
#include "serial_signal.h"
#include "common.h"
#include "serial_tty.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/

/* Static Function Declarations ***************************************************************************************/
static void serial_init(uint8_t threadId, SerialPort* port);
/* Global Function Definitions ****************************************************************************************/
void* serial_thread_start(void* arg)
{
    /* TODO: arg need to have id of thread */
    uint8_t threadId = (*(uint8_t*)(arg));
    SerialPort* port = NULL;
    serial_init(threadId, port);
    while(1)
    {
        /* check signal and handle it */
        if(serial_signal_check_signal(threadId))
        {
            LOG_INFO("Signal is waiting in queue\n");
            SignalS* signal = serial_signal_get(threadId);
            serial_signal_handler(signal);
        }
    }
    /* here thread will end*/
}

void serial_signal_handler(SignalS* signal)
{
    LOG_DEBUG("Handling signal");
    (void)signal;
}

static void serial_init(uint8_t threadId, SerialPort* port) {
    if(threadId == 5) {
        //open stm32
        port = serial_create(B1152000, ONE, NONE, EIGHT, false, "/dev/ttyUSB0");
        serial_openPort(port);
    }
}
/* Static Function Definitions ****************************************************************************************/

/*void* serial_thread(void* arg) {
    int i = 0;
    //ARG is a pointer to serialPort so dereference it
    SerialPort* serial = (SerialPort*)(arg);
    serial_openPort(serial);
    while(1) {
        char temp[255];
        if(i % 2 == 0) {
            char msg[] = {'1'};
            serial_write(msg , serial);
            LOG_INFO("Succesful write %s", msg);
        }
        else {
            char msg[] = {'2'};
            serial_write(msg , serial);
            LOG_INFO("Succesful write %s", msg);
        }
        serial_read(255, temp, serial);
        LOG_INFO("Succesful read %s", temp);
        printf("%s", temp);
        sleep(1);
        i++;
    }
}*/