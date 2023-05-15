#include "serial_thread.h"
#include "serial_signal.h"
#include "messages_micro_req.h"
#include "messages_micro.h"
#include "common.h"

void* serial_thread_start(void* arg)
{
    //NOTE: arg need to be pointer to uint8_t
    uint8_t threadId = (*(uint8_t*)(arg));

    while(1)
    {
        /* check signal and handle it */
        if(serial_signal_check_signal(threadId))
        {
            LOG_INFO("[%d thread ] Signal is waiting in queue\n", threadId);
            SignalS* signal = serial_signal_get(threadId);
            serial_signal_handler(signal);
        }
    }
    /* here thread will end*/
}

void serial_signal_handler(SignalS* signal)
{
    LOG_DEBUG("Handling signal");
    MessageMicroReqS* payload = common_signal_get_payload(signal);

    /*  its a problem becose we create in many places this same code, maybe send to microcontroler number based on
        this type, i think this should be better resolve of this problem*/

    /*TODO: UART connection with microcontroler */
    LOG_INFO("Sending via UART to %d microcontroler %d request", payload->micro, payload->request);

}

