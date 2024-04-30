#ifndef EXERCISE2_PORT_H
#define EXERCISE2_PORT_H

#include <Windows.h>
#include <iostream>
#include <vector>

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
    bool send(const std::vector<uint8_t>& data);
    bool receive(std::vector<uint8_t>& buffer, size_t length);
};

#endif //EXERCISE2_PORT_H
