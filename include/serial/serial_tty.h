#ifndef SERIAL_TTY_H
#define SERIAL_TTY_H
#include "serial_types.h"
typedef struct SerialPort SerialPort;
/**
 * Serial port is setting all parametrs to identify connection to serial port
 */
SerialPort* serial_create(Serial_BaudRate baudRate,
                        Serial_StopBits stopBits,
                        Serial_ParityBit parityBit,
                        Serial_DataBits dataBits,
                        bool echo,
                        const char* device);
/**
 * Constructor for SerialPort
 */
void serial_openPort(SerialPort* serial);
/**
 * Opening serialPort
 */
void serial_closePort(SerialPort* serial);
void serial_close(SerialPort* serial);

int serial_read(size_t buffSize, char buff[buffSize], SerialPort* serial);
int serial_write(const char* msg, SerialPort* serial);
void serial_setBaudRate(Serial_BaudRate baudRate, SerialPort* serial);
void serial_setStopBits(Serial_StopBits stopBits, SerialPort* serial);
void serial_setParityBits(Serial_ParityBit parityBit, SerialPort* serial);
void serial_setDataBits(Serial_DataBits dataBits, SerialPort* serial);
void serial_setDevice(const char* device, SerialPort* serial);
void serial_setEcho(bool Enabled, SerialPort* serialPort);
#endif //SERIAL_TTY_H