#ifndef EXERCISE2_PORT_H
#define EXERCISE2_PORT_H

#include <Windows.h>
#include <iostream>
#include <vector>
#include <cstdint>

#define SOH 0x01
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15
#define CAN 0x18
#define C 0x43

class port {
public:
    HANDLE handle;
    DCB setupPort;
    COMMTIMEOUTS timeouts;
    COMSTAT portResources;
    DWORD error;

    port();
    ~port();
    void openPort();
    void send(char* sign, int length);
    void receive(char* sign,int length);
    void receive(char* sign, unsigned long sizeOfSign);
};

#endif //EXERCISE2_PORT_H
