#include "../include/port.h"

std::string portName = "COM1";

port::port() {
    openPort();

    if (handle != INVALID_HANDLE_VALUE) {
        std::cout << "dupa" << std::endl;
    } else {
        std::cout << "Connection failed. Check if the port exists or is not already occupied." << std::endl;
        exit(1);
    }
}

port::~port() = default;

void port::openPort() {
    handle = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open port. Error code: " << GetLastError() << std::endl;
    }
}