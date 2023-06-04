#include "serial_tty.h"
#include "serial_types.h"
/*
 * Declared struct SerialPort for hiden private members
 */
typedef struct SerialPort{
    Serial_BaudRate baudRate;
    Serial_StopBits stopBits;
    Serial_ParityBit parityBit;
    Serial_DataBits dataBits;
    Serial_State state;
    int echo;
    int timeout;
    int fileDesc;
    struct termios termios;
    const char* device;
}SerialPort;
/*
 * Private members declared here
 */
void serial_p_getTermios(SerialPort* serial);
void serial_p_setTermios(SerialPort* serial);
void serial_p_setDataBits(SerialPort* serial);
void serial_p_setParityBits(SerialPort* serial);
void serial_p_setStopBits(SerialPort* serial);
void serial_p_setBaudRate(SerialPort* serial);
void serial_p_setTimeout(SerialPort* serial);
void serial_p_setInputFlags(SerialPort* serial);
void serial_p_setOutputFlags(SerialPort* serial);
void serial_p_setEcho(SerialPort* serial);
void serial_p_configure(SerialPort* serial);
/*******************************************************************************************************
 *                                    IMPLEMENTATION PRIVATE MEMBERS                                   *
 ******************************************************************************************************/

void serial_p_getTermios(SerialPort* serial) {
    ioctl(serial->fileDesc, TCGETS, &(serial->termios));
}

void serial_p_setTermios(SerialPort* serial) {
    ioctl(serial->fileDesc, TCSETS, &serial->termios);
}

void serial_p_setDataBits(SerialPort* serial) {
    serial->termios.c_cflag &= (uint)(~CSIZE);
    switch (serial->dataBits) {
        case FIVE:
            serial->termios.c_cflag |= CS5;
            LOG_INFO("Data bits sets to FIVE for FD = %d", serial->fileDesc);
            break;
        case SIX:
            serial->termios.c_cflag |= CS6;
            LOG_INFO("Data bits sets to SIX for FD = %d", serial->fileDesc);
            break;
        case SEVEN:
            serial->termios.c_cflag |= CS7;
            LOG_INFO("Data bits sets to SEVEN for FD = %d", serial->fileDesc);
            break;
        case EIGHT:
            serial->termios.c_cflag |= CS8;
            LOG_INFO("Data bits sets to EIGHT for FD = %d", serial->fileDesc);
            break;
    }
}

void serial_p_setParityBits(SerialPort* serial) {
    switch (serial->parityBit) {
        case NONE:
            serial->termios.c_cflag &= (uint)(~PARENB);
            LOG_INFO("Parity bits sets to NONE for FD = %d", serial->fileDesc);
            break;
        case EVEN:
            serial->termios.c_cflag |= (uint)(PARENB);
            serial->termios.c_cflag &= (uint)(~PARODD);
            LOG_INFO("Parity bits sets to EVEN for FD = %d", serial->fileDesc);
            break;
        case ODD:
            serial->termios.c_cflag |= (uint)(PARENB);
            serial->termios.c_cflag |= (uint)(PARODD);
            LOG_INFO("Parity bits sets to ODD for FD = %d", serial->fileDesc);
            break;
    }
}

void serial_p_setStopBits(SerialPort* serial) {
    switch(serial->stopBits){
        case ONE:
            serial->termios.c_cflag &= (uint)(~CSTOPB);
            LOG_INFO("Stop bits sets to ONE for FD = %d", serial->fileDesc);
            break;
        case TWO:
            serial->termios.c_cflag |= (uint)(CSTOPB);
            LOG_INFO("Stop bits sets to TWO for FD = %d", serial->fileDesc);
            break;
    }
}

void serial_p_setBaudRate(SerialPort* serial) {
    serial->termios.c_cflag |= (uint)(CREAD | CLOCAL);

    serial->termios.c_cflag &= (uint)(~CBAUD);
    serial->termios.c_cflag |= (uint)(CBAUDEX);
    switch(serial->baudRate) {
        case B_0:
            serial->termios.c_ispeed = 0;
            serial->termios.c_ospeed = 0;
            LOG_INFO("Baud rate set to 0 for FD = %d", serial->fileDesc);
            break;
        case B_50:
            serial->termios.c_ispeed = 50;
            serial->termios.c_ospeed = 50;
            LOG_INFO("Baud rate set to 50 for FD = %d", serial->fileDesc);
            break;
        case B_75:
            serial->termios.c_ispeed = 75;
            serial->termios.c_ospeed = 75;
            LOG_INFO("Baud rate set to 75 for FD = %d", serial->fileDesc);
            break;
        case B_110:
            serial->termios.c_ispeed = 110;
            serial->termios.c_ospeed = 110;
            LOG_INFO("Baud rate set to 110 for FD = %d", serial->fileDesc);
            break;
        case B_134:
            serial->termios.c_ispeed = 134;
            serial->termios.c_ospeed = 134;
            LOG_INFO("Baud rate set to 134 for FD = %d", serial->fileDesc);
            break;
        case B_150:
            serial->termios.c_ispeed = 150;
            serial->termios.c_ospeed = 150;
            LOG_INFO("Baud rate set to 150 for FD = %d", serial->fileDesc);
            break;
        case B_200:
            serial->termios.c_ispeed = 200;
            serial->termios.c_ospeed = 200;
            LOG_INFO("Baud rate set to 200 for FD = %d", serial->fileDesc);
            break;
        case B_300:
            serial->termios.c_ispeed = 300;
            serial->termios.c_ospeed = 300;
            LOG_INFO("Baud rate set to 300 for FD = %d", serial->fileDesc);
            break;
        case B_600:
            serial->termios.c_ispeed = 600;
            serial->termios.c_ospeed = 600;
            LOG_INFO("Baud rate set to 600 for FD = %d", serial->fileDesc);
            break;
        case B_1200:
            serial->termios.c_ispeed = 1200;
            serial->termios.c_ospeed = 1200;
            LOG_INFO("Baud rate set to 1200 for FD = %d", serial->fileDesc);
            break;
        case B_1800:
            serial->termios.c_ispeed = 1800;
            serial->termios.c_ospeed = 1800;
            LOG_INFO("Baud rate set to 1800 for FD = %d", serial->fileDesc);
            break;
        case B_2400:
            serial->termios.c_ispeed = 2400;
            serial->termios.c_ospeed = 2400;
            LOG_INFO("Baud rate set to 2400 for FD = %d", serial->fileDesc);
            break;
        case B_4800:
            serial->termios.c_ispeed = 4800;
            serial->termios.c_ospeed = 4800;
            LOG_INFO("Baud rate set to 4800 for FD = %d", serial->fileDesc);
            break;
        case B_9600:
            serial->termios.c_ispeed = 9600;
            serial->termios.c_ospeed = 9600;
            LOG_INFO("Baud rate set to 9600 for FD = %d", serial->fileDesc);
            break;
        case B_19200:
            serial->termios.c_ispeed = 19200;
            serial->termios.c_ospeed = 19200;
            LOG_INFO("Baud rate set to 19200 for FD = %d", serial->fileDesc);
            break;
        case B_38400:
            serial->termios.c_ispeed = 38400;
            serial->termios.c_ospeed = 38400;
            LOG_INFO("Baud rate set to 38400 for FD = %d", serial->fileDesc);
            break;
        case B_57600:
            serial->termios.c_ispeed = 57600;
            serial->termios.c_ospeed = 57600;
            LOG_INFO("Baud rate set to 57600 for FD = %d", serial->fileDesc);
            break;
        case B_115200:
            serial->termios.c_ispeed = 115200;
            serial->termios.c_ospeed = 115200;
            LOG_INFO("Baud rate set to 115200 for FD = %d", serial->fileDesc);
            break;
        case B_230400:
            serial->termios.c_ispeed = 230400;
            serial->termios.c_ospeed = 230400;
            LOG_INFO("Baud rate set to 230400 for FD = %d", serial->fileDesc);
            break;
        case B_460800:
            serial->termios.c_ispeed = 460800;
            serial->termios.c_ospeed = 460800;
            LOG_INFO("Baud rate set to 460800 for FD = %d", serial->fileDesc);
            break;
    }
}

void serial_p_setTimeout(SerialPort* serial) {
    if(serial->timeout == -1) {
        serial->termios.c_cc[VTIME] = 0;
        serial->termios.c_cc[VMIN] = 1;
    }
    else if(serial->timeout == 0) {
        serial->termios.c_cc[VTIME] = 0;
        serial->termios.c_cc[VMIN] = 0;
    }
    else if(serial->timeout > 0) {
        serial->termios.c_cc[VTIME] = (cc_t)(serial->timeout/100);
        serial->termios.c_cc[VMIN] = 0;
    }
    else {
        serial->termios.c_cc[VTIME] = 0;
        serial->termios.c_cc[VMIN] = (cc_t) (-serial->timeout);
    }
}

void serial_p_setEcho(SerialPort* serial) {
    if(serial->echo) {
        serial->termios.c_lflag |= (uint)(ECHO);
    } else {
        serial->termios.c_lflag &= (uint)(~ECHO);
    }
    serial->termios.c_lflag		&= (uint)(~ICANON);
    serial->termios.c_lflag		&= (uint)(~ECHOE);
    serial->termios.c_lflag		&= (uint)(~ECHONL);
    serial->termios.c_lflag		&= (uint)(~ISIG);
}

void serial_p_setInputFlags(SerialPort* serial) {
    serial->termios.c_iflag &= (uint)(~(IXON | IXOFF | IXANY));
    serial->termios.c_iflag &= (uint)(~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL));
}

void serial_p_setOutputFlags(SerialPort* serial) {
    serial->termios.c_oflag = 0;
    serial->termios.c_oflag &= (uint)(~OPOST);
}

void serial_p_configure(SerialPort* serialPort) {
    serial_p_getTermios(serialPort);
    serial_p_setDataBits(serialPort);
    serial_p_setParityBits(serialPort);
    serial_p_setStopBits(serialPort);
    serial_p_setBaudRate(serialPort);
    serial_p_setTimeout(serialPort);
    serial_p_setInputFlags(serialPort);
    serial_p_setOutputFlags(serialPort);
    serial_p_setEcho(serialPort);
    serial_p_setTermios(serialPort);
}
/*******************************************************************************************************
 *                           IMPLEMENTATION CONSTRUCTOR AND DESTRUCTOR                                 *
 ******************************************************************************************************/
SerialPort* serial_create(Serial_BaudRate baudRate,
                        Serial_StopBits stopBits,
                        Serial_ParityBit parityBit,
                        Serial_DataBits dataBits,
                        bool echo,
                        const char* device) {

    SerialPort* serialPort = malloc(sizeof(SerialPort));
    if(serialPort == NULL) {
        perror("Failed allocated memory, aborted");
        LOG_FATAL("CAN'T ALLOC MEMORY");
        return NULL;
    }
    serialPort->device = device;
    serialPort->baudRate = baudRate;
    serialPort->parityBit = parityBit;
    serialPort->dataBits = dataBits;
    serialPort->stopBits = stopBits;
    serialPort->echo = echo;
    serialPort->timeout = -1;
    serialPort->fileDesc = -1;
    serial_openPort(serialPort);
    serial_p_configure(serialPort);

    return serialPort;
}

void serial_close(SerialPort* serial) {
    close(serial->fileDesc);
    serial->state = CLOSED;
    free(serial);
}
void serial_closePort(SerialPort* serial) {
    close(serial->fileDesc);
    serial->state = CLOSED;
}

void serial_openPort(SerialPort* serial) {
    if(serial->device == NULL) {
        perror("Cant open file when device is nullptr");
        LOG_ERROR("Can't open nullptr file");
    }
    serial->fileDesc = open(serial->device, O_RDWR);
    if(serial->fileDesc == -1){
        perror("Cant open file ");
        LOG_ERROR("Can't open %s file", serial->device);
    }
    serial->state = OPEN;
}
/*******************************************************************************************************
 *                                     IMPLEMENTATION SETTERS FUNCTIONS                                *
 ******************************************************************************************************/

void serial_setBaudRate(Serial_BaudRate baudRate, SerialPort* serial) {
    serial->baudRate = baudRate;
    if(serial->state == OPEN) {
        serial_p_configure(serial);
    }
}
void serial_setStopBits(Serial_StopBits stopBits, SerialPort* serial) {
    serial->stopBits = stopBits;
    if(serial->state == OPEN) {
        serial_p_configure(serial);
    }
}
void serial_setParityBits(Serial_ParityBit parityBit, SerialPort* serial) {
    serial->parityBit = parityBit;
    if(serial->state == OPEN) {
        serial_p_configure(serial);
    }
}
void serial_setDataBits(Serial_DataBits dataBits, SerialPort* serial) {
    serial->dataBits = dataBits;
    if(serial->state == OPEN) {
        serial_p_configure(serial);
    }
}
void serial_setDevice(const char* device, SerialPort* serial) {
    serial->device = device;
    if(serial->state == OPEN) {
        serial_p_configure(serial);
    }
}
void serial_setEcho(bool Enabled, SerialPort* serial) {
    serial->echo = Enabled;
    if(serial->state == OPEN) {
        serial_p_configure(serial);
    }
}
/*******************************************************************************************************
 *                                     IMPLEMENTATION WRITE READ FUNCTIONS                             *
 ******************************************************************************************************/
int serial_write(const char* msg, SerialPort* serial) {
    ssize_t writeResult;
    if(serial == NULL) {
        LOG_ERROR("Serial is null pointer");
        return -1;
    }
    if(serial->state == CLOSED) {
       LOG_ERROR("Write to closed port");
       return SERIAL_E_WRITE;
   }
   if(serial->fileDesc < 0) {
       LOG_ERROR("Write to port with file descriptor < 0");
       return SERIAL_E_WRITE;
   }
   writeResult = write(serial->fileDesc, msg, sizeof(char));
   return (int)writeResult;
}

int serial_read(size_t buffSize, char buff[buffSize], SerialPort* serial) {
    ssize_t nRead;
    if(serial->state == CLOSED) {

        LOG_ERROR("Write to closed port");
        return SERIAL_E_READ;
    }
    if(serial->fileDesc < 0) {

        LOG_ERROR("Write to port with file descriptor < 0");
        return SERIAL_E_READ;
    }
    nRead = read(serial->fileDesc, buff, buffSize);
    if(nRead < 0) {
        LOG_ERROR("Cant read nRead < 0");
        return SERIAL_E_READ;
    }
    else if(nRead == 0) {
        LOG_ERROR("Cant read nRead == 0 ");
        return SERIAL_E_READ;
    }
    else {
        return 0;
    }
}
