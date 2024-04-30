#include <iostream>
#include "../include/port.h"

int main() {
    port port;
    std::vector<uint8_t> dataToSend = {0x41, 0x42, 0x43, 0x44};
    bool success = port.send(dataToSend);

    if (success) {
        std::cout << "uwu" << std::endl;
    } else {
        std::cerr << "not uwu" << std::endl;
    }
    return 0;
}
