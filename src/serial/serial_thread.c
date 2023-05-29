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
#include "messages.h"
/* Definitions ********************************************************************************************************/

/* Type Declarations **************************************************************************************************/

/* Global Variable Definitions ****************************************************************************************/

/* Local Variable Definitions *****************************************************************************************/
static void serial_signal_handler(SignalS* signal, SerialPort* port);
/* Static Function Declarations ***************************************************************************************/
static SerialPort* serial_init(uint8_t threadId);
/* Global Function Definitions ****************************************************************************************/
void* serial_thread_start(void* arg)
{
    /* TODO: arg need to have id of thread */
    uint8_t threadId = (*(uint8_t*)(arg));
    SerialPort* port = serial_init(threadId);
    while(1)
    {
        /* check signal and handle it */
        if(serial_signal_check_signal(threadId))
        {
            LOG_INFO("Signal is waiting in queue\n");
            SignalS* signal = serial_signal_get(threadId);
            serial_signal_handler(signal, port);
        }
    }
    /* here thread will end*/
}

void serial_signal_handler(SignalS* signal, SerialPort* port)
{
    LOG_DEBUG("Handling signal");
    /* check what we need to send via serial and send it ;d*/
    MessageMicroReqS* req = common_signal_get_payload(signal);
    char buff[100];
    memcpy(buff, &req->request, sizeof(uint16_t));
    serial_write(buff, port);
    (void)signal;
}

static SerialPort* serial_init(uint8_t threadId) {
    SerialPort* port;
    if(threadId == 5) {
        //open stm32
        port = serial_create(B1152000, ONE, NONE, EIGHT, false, "/dev/ttyUSB1");
        serial_openPort(port);
    }
    if(threadId == 6) {
        //open arduino
        port = serial_create(B1152000, ONE, NONE, EIGHT, false, "/dev/ttyUSB0");
        serial_openPort(port);
    }
    return port;
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