#include "../include/port.h"

std::string portName = "COM1";

port::port() {
    openPort();

    if (handle != INVALID_HANDLE_VALUE) {
        setupPort.DCBlength = sizeof(setupPort);
        GetCommState(handle, &setupPort);
        setupPort.BaudRate = CBR_9600;
        setupPort.Parity = NOPARITY;
        setupPort.StopBits = ONESTOPBIT;
        setupPort.ByteSize = 8;

        SetCommState(handle, &setupPort);
        SetCommTimeouts(handle, &timeouts);
        ClearCommError(handle, &error, &portResources);
    } else {
        std::cout << "Connection failed. Check if the port exists or is not already occupied." << std::endl;
        exit(1);
    }
}

port::~port() = default;

void port::openPort() {
    handle = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                        OPEN_EXISTING, 0, NULL);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open port. Error code: " << GetLastError() << std::endl;
    }
}

bool port::send(const std::vector<uint8_t>& data) {
    DWORD numOfWrittenBytes;
    return WriteFile(handle, data.data(), data.size(), &numOfWrittenBytes, NULL) != 0;
}