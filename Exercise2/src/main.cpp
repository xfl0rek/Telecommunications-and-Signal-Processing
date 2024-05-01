#include <iostream>
#include "../include/port.h"
#include "../include/utility.h"

int main() {
    port port;
    std::vector<uint8_t> dataToSend = {0x41, 0x42, 0x43, 0x44};
    bool success = port.send(dataToSend);

    if (success) {
        std::cout << "uwu" << std::endl;
    } else {
        std::cerr << "not uwu" << std::endl;
    }

    std::vector<uint8_t> receivedData = {0xAA, 0xBB, 0xCC, 0xDD};
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

    const char* data = "Hello, world!";
    int dataSize = 13;

    char* mutableData = const_cast<char*>(data);

    uint16_t crc = utility::calculateCRC(mutableData, dataSize);

    std::cout << "CRC: " << std::hex << crc << std::endl;

    int checksum = utility::calculateChecksum(data);

    std::cout << "Checksum: " << checksum << std::endl;

    return 0;
}
