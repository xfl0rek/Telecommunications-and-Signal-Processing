#ifndef EXERCISE2_RECEIVER_H
#define EXERCISE2_RECEIVER_H

#include "../include/port.h"

class receiver {
private:
    port* Port;

public:
    explicit receiver(port* port);
    ~receiver();
    void receive(bool withCRC);
};

#endif //EXERCISE2_RECEIVER_H
