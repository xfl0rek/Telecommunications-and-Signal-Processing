#include "../include/transmitter.h"
#include "../include/utility.h"
#include "../include/globals.h"

const char SOH_ = 0x01;
const char NAK_ = 0x15;
const char CAN_ = 0x18;
const char ACK_ = 0x06;
const char EOT_ = 0x04;
const char C_ = 0x43;

transmitter::transmitter(port *port) : Port(port) {}

transmitter::~transmitter() = default;

void transmitter::transmit() {
    packetNum = 1;
    std::cout << "Enter the name of the file you want to send\n";
    std::cin >> filename;

    std::cout << "\nWaiting for transmission to start...\n";
    for (int i = 0; i < 6; i++) {
        Port->receive(&sign, numOfSigns);

        if (sign == C_) {
            std::cout << "\nReceived C (CRC) character \n" << sign << std::endl;
            Sleep(5000);
            isCRC = true;
            connection = true;
            break;
        } else if (sign == NAK_) {
            std::cout << "\nReceived NAK (Checksum) character \n" << sign << std::endl;
            Sleep(5000);
            isCRC = false;
            connection = true;
            break;
        }
    }
    if (!connection) exit(1);

    file2.open(filename, std::ios::binary);
    while (!file2.eof()) {
        int x = 0;
        while (x < 128 && !file2.eof()) {
            dataBlock[x] = file2.get();
            if (file2.eof()) break;
            x++;
        }
        isCorrectPacket = false;

        while (!isCorrectPacket) {
            std::cout << "Sending packet. Please wait...\n";
            sign = SOH_;
            Port->send(&sign, numOfSigns);

            sign = (char)packetNum;
            Port->send(&sign, numOfSigns);

            sign = (char)255 - packetNum;
            Port->send(&sign, numOfSigns);

            Port->send(dataBlock, 128);

            if (!isCRC) {
                char checksum = NULL;
                checksum += utility::calculateChecksum(dataBlock);
                Port->send(&checksum, numOfSigns);
            } else {
                tmpCRC = utility::calculateCRC(dataBlock, 128);
                sign = utility::calculateCRCByte(tmpCRC, 1);
                Port->send(&sign, numOfSigns);
                sign = utility::calculateCRCByte(tmpCRC, 2);
                Port->send(&sign, numOfSigns);
            }

            while (1) {
                Port->receive(&sign, sizeOfSign);

                if (sign == ACK_) {
                    isCorrectPacket = true;
                    std::cout << "Packet data sent successfully!\n";
                    break;
                }
                if (sign == NAK_) {
                    std::cout << "ERROR - received NAK!\n";
                    break;
                }
                if (sign == CAN_) {
                    std::cout << "ERROR - connection terminated!\n";
                    exit (1);
                }
            }
        }
        if (packetNum == 255) packetNum = 1;
        else packetNum++;

    }
    file2.close();

    while (1) {
        sign = EOT_;
        Port->send(&sign, numOfSigns);
        Port->receive(&sign, sizeOfSign);
        if (sign == ACK_) break;
    }

    std::cout << "File sent.\n";
    Sleep(5000);
}
