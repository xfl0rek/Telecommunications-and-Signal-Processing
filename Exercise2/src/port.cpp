#include "../include/port.h"
#include "../include/globals.h"

std::string portName = "COM5";

port::port() {
    openPort();

    if (handle != INVALID_HANDLE_VALUE) {
        setupPort.DCBlength = sizeof(setupPort);
        GetCommState(handle, &setupPort);
        setupPort.BaudRate = CBR_9600;
        setupPort.Parity = NOPARITY;
        setupPort.StopBits = ONESTOPBIT;
        setupPort.ByteSize = 8;

        setupPort.fParity = TRUE;
        setupPort.fDtrControl = DTR_CONTROL_DISABLE;
        setupPort.fRtsControl = RTS_CONTROL_DISABLE;
        setupPort.fOutxCtsFlow = FALSE;
        setupPort.fOutxDsrFlow = FALSE;
        setupPort.fDsrSensitivity = FALSE;
        setupPort.fAbortOnError = FALSE;
        setupPort.fOutX = FALSE;
        setupPort.fInX = FALSE;
        setupPort.fErrorChar = FALSE;
        setupPort.fNull = FALSE;

        timeouts.ReadIntervalTimeout = 10000;
        timeouts.ReadTotalTimeoutMultiplier = 10000;
        timeouts.ReadTotalTimeoutConstant = 10000;
        timeouts.WriteTotalTimeoutMultiplier = 100;
        timeouts.WriteTotalTimeoutConstant = 100;

        SetCommState(handle, &setupPort);
        SetCommTimeouts(handle, &timeouts);
        ClearCommError(handle, &error, &portResources);
    } else {
        std::cout << "Connection failed. Check if the port exists or is not already occupied." << std::endl;
        exit(1);
    }
}

port::~port() {
    CloseHandle(handle);
}

void port::openPort() {
    handle = CreateFile(portName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL,
                        OPEN_EXISTING, 0, NULL);

    if (handle == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to open port. Error code: " << GetLastError() << std::endl;
    }
}

void port::send(char *sign, int length) {
    DWORD num;
    WriteFile(handle, sign, length, &num, NULL);
}

void port::receive(char *sign, int length) {
    DWORD pos = 0, num;
    while (pos < length) {
        ReadFile(handle, sign + pos, length - pos, &num, NULL);
        pos += num;
    }
}

void port::receive(char *sign, unsigned long sizeOfSign) {
    ReadFile(handle, sign, 1, &sizeOfSign, NULL);
}