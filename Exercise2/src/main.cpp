#include "../include/port.h"
#include "../include/transmitter.h"
#include "../include/receiver.h"

int main() {
    port port;
//    transmitter transmitter(&port);
//    transmitter.transmit();
    receiver receiver(&port);
    receiver.receive(false);
    //port.communicationTest();
    return 0;
}
