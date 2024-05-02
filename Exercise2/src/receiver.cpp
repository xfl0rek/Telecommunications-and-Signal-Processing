#include "../include/receiver.h"
#include "../include/utility.h"
#include "../include/globals.h"

const char SOH_ = 0x01;
const char NAK_ = 0x15;
const char CAN_ = 0x18;
const char ACK_ = 0x06;
const char EOT_ = 0x04;
const char C_ = 0x43;

receiver::receiver(port* port) : Port(port) {}

receiver::~receiver() = default;

void receiver::receive(bool withCRC) {
    std::cout << "Enter the filename:\n";
    std::cin >> filename;

    if (!withCRC) {
        sign = NAK_;
        isCRC = false;
    }
    else {
        sign = C_;
        isCRC = true;
    }

    for (int i = 0; i < 6; i++) {
        std::cout << "\nSending...\n";
        Port->send(&sign, numOfSigns);

        std::cout << "Waiting...\n";
        Port->receive(first3Bytes, 3);
        std::cout << sign << std::endl;
        if (first3Bytes[0] == SOH) {
            std::cout << "Connected\n";
            connection = true;
            break;
        }
    }

    if (!connection) {
        std::cout << "Failed to connect.\n";
        exit(1);
    }

    file.open(filename, std::ios::binary);
    std::cout << "RECEIVING...\n";

    packetNum = (int)first3Bytes[1];
    complementTo255 = first3Bytes[2];
    Port->receive(dataBlock, 128);

    if (withCRC) {
        Port->receive(errorControlSum, 2);
        isCorrectPacket = true;

        if ((char)(255 - packetNum) != complementTo255) {
            std::cout << "Incorrect packet number!\n";
            sign = NAK_;
            Port->send(&sign, numOfSigns);
            isCorrectPacket = false;

        }

        if (isCorrectPacket) {
            for (char i : dataBlock) {
                if (i != 26)
                    file << i;
            }
            std::cout << "Packet sent.\n";
            sign = ACK_;
            Port->send(&sign, numOfSigns);
        }
        while (1) {
            Port->receive(&sign, sizeOfSign);
            if (sign == EOT || sign == CAN) break;
            std::cout << "Receiving...\n";

            Port->receive(&sign, sizeOfSign);
            packetNum = (int)sign;

            Port->receive(&sign, sizeOfSign);
            complementTo255 = sign;

            Port->receive(dataBlock, 128);
            Port->receive(errorControlSum, 2);

            isCorrectPacket = true;
            if ((char)(255 - packetNum) != complementTo255) {
                std::cout << "Incorrect packet number!\n";
                sign = NAK_;
                Port->send(&sign, numOfSigns);
                isCorrectPacket = false;
            } else {
                tmpCRC = utility::calculateCRC(dataBlock, 128);

                if (utility::calculateCRCByte(tmpCRC, 1) != errorControlSum[0] || utility::calculateCRCByte(tmpCRC, 2) != errorControlSum[1]) {
                    std::cout << "Incorrect checksum!\n";
                    sign = NAK_;
                    Port->send(&sign, numOfSigns);
                    isCorrectPacket = false;
                }
            }
            if (isCorrectPacket) {
                for (char i : dataBlock) {
                    if (i != 26)
                        file << i;
                }

                std::cout << "Packet transmission successful!\n";
                sign = ACK_;
                Port->send(&sign, numOfSigns);
            }
        }
    } else {

        Port->receive(errorControlSum, 1);
        isCorrectPacket = true;

        if ((char)(255 - packetNum) != complementTo255) {
            std::cout << "Incorrect packet number!\n";
            sign = NAK_;
            Port->send(&sign, numOfSigns);
            isCorrectPacket = false;

        }

        if (isCorrectPacket) {
            for (char i : dataBlock) {
                if (i != 26)
                    file << i;
            }
            std::cout << "Packet sent.\n";
            WriteFile(Port->handle, &ACK_, numOfSigns, &sizeOfSign, NULL);
        }

        while (1) {
            Port->receive(&sign, sizeOfSign);
            if (sign == EOT || sign == CAN) break;
            std::cout << "Receiving...\n";

            Port->receive(&sign, sizeOfSign);
            packetNum = (int)sign;

            Port->receive(&sign, sizeOfSign);
            complementTo255 = sign;

            Port->receive(dataBlock, 128);

            Port->receive(&sign, sizeOfSign);
            errorControlSum[0] = sign;

            isCorrectPacket = true;
            if ((char)(255 - packetNum) != complementTo255) {
                std::cout << "Incorrect packet number!\n";
                sign = NAK_;
                Port->send(&sign, numOfSigns);
                isCorrectPacket = false;
            } else {
                tmpCRC = utility::calculateChecksum(dataBlock);

                if (utility::calculateCRCByte(tmpCRC, 1) != errorControlSum[0]) {
                    std::cout << "Incorrect checksum!\n";
                    sign = NAK_;
                    Port->send(&sign, numOfSigns);
                    isCorrectPacket = false;
                }
            }
            if (isCorrectPacket) {
                for (char i : dataBlock) {
                    if (i != 26)
                        file << i;
                }

                std::cout << "Packet transmission successful!\n";
                sign = ACK_;
                Port->send(&sign, numOfSigns);
            }
        }
    }
    sign = ACK_;
    Port->send(&sign, numOfSigns);

    file.close();

    if (sign == CAN) std::cout << "ERROR - connection terminated! \n";
    else std::cout << "File received.\n";
    std::cin.get();
}
