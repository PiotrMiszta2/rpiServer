#ifndef SERIAL_TYPES_H
#define SERIAL_TYPES_H

#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "logger.h"
#define SERIAL_E_WRITE      -1
#define SERIAL_E_READ       -2
typedef enum Serial_BaudRate {
    B_0,
    B_50,
    B_75,
    B_110,
    B_134,
    B_150,
    B_200,
    B_300,
    B_600,
    B_1200,
    B_1800,
    B_2400,
    B_4800,
    B_9600,
    B_19200,
    B_38400,
    B_57600,
    B_115200,
    B_230400,
    B_460800,
}Serial_BaudRate;

typedef enum Serial_DataBits{
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
}Serial_DataBits;

typedef enum Serial_StopBits{
    ONE,
    TWO,
}Serial_StopBits;

typedef enum Serial_ParityBit{
    NONE,
    EVEN,
    ODD,
}Serial_ParityBit;

typedef enum Serial_State {
    CLOSED,
    OPEN,
}Serial_State;


#endif //SERIAL_TYPES_H