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

    std::vector<uint8_t> receivedData(10);
    bool success2 = port.receive(receivedData, receivedData.size());

    if (success2) {
        std::cout << "Received data:" << std::endl;
        for (const auto& byte : receivedData) {
            std::cout << std::hex << static_cast<int>(byte) << " ";
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Error." << std::endl;
    }

    return 0;
}
