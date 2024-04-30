#ifndef EXERCISE2_PORT_H
#define EXERCISE2_PORT_H

#include <Windows.h>
#include <iostream>

#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15
#define CAN 0x18
#define C 0x43

class port {
private:
    HANDLE handle;
    DCB setupPort;
    COMMTIMEOUTS timeouts;
    COMSTAT portResources;
    DWORD error;

public:
    port();
    ~port();
    void openPort();
};

#endif //EXERCISE2_PORT_H
