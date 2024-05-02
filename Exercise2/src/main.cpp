#include "../include/port.h"
#include "../include/transmitter.h"
#include "../include/receiver.h"

int main() {
    port port;
    bool menu = false;
    bool isCRC;

    while(!menu) {
        system("cls");
        std::cout << "Choose operation mode:" << std::endl;
        std::cout << "1. Receiver" << std::endl;
        std::cout << "2. Transmitter" << std::endl;
        std::cout << "3. End program." << std::endl << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
            {
                int checksum;
                std::cout << "Choose the type of error control:" << std::endl;
                std::cout << "1. CRC (C)" << std::endl;
                std::cout << "2. Checksum (NAK)" << std::endl;
                std::cin >> checksum;
                if (checksum == 1) {
                    isCRC = true;
                } else {
                    isCRC = false;
                }
                receiver receiver(&port);
                receiver.receive(isCRC);
                break;
            }
            case 2: {
                transmitter transmitter(&port);
                transmitter.transmit();
                break;
            }
            case 3: {
                menu = true;
                break;
            }
            default:
                break;
        }
    }

    return 0;
}
