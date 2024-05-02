#ifndef EXERCISE2_TRANSMITTER_H
#define EXERCISE2_TRANSMITTER_H

#include "../include/port.h"

class transmitter {
private:
    port* Port;

public:
    transmitter(port* port);
    ~transmitter();
    void transmit();
};

#endif //EXERCISE2_TRANSMITTER_H
