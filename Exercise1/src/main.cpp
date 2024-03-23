#include <iostream>
#include "../include/singleErrorCode.h"
#include "../include/doubleErrorCode.h"
#include "../include/algorithm.h"
#include <fstream>

int main() {
    int choice;

    std::cout << "1. zakoduj" << std::endl;
    std::cout << "2. odkoduj" << std::endl;

    std::cin >> choice;

    switch (choice) {
        case 1: {
            algorithm::preparationForTransmission(doubleErrorMatrix);
            break;
        }
        case 2: {
            std::fstream file("../message.txt");
            if (!file.is_open()) {
                std::cerr << "Failed to open the file." << std::endl;
                break;
            }

            std::string message;
            if (!std::getline(file, message)) {
                std::cerr << "Failed to read the message." << std::endl;
                file.close();
                break;
            }

            file.close();

            std::cout << "Poprawna wiadomosc: " << message << std::endl;

            std::vector<bool> binary = algorithm::textToBinary(message, doubleErrorMatrix);

            std::cout << "Poprawna wiadomosc na bity: ";
            for (const bool v : binary) {
                std::cout << v;
            }
            std::cout << std::endl;

            std::vector<bool> codedMessage;
            std::fstream codedFile("../codedMessage.txt");
            if (!codedFile.is_open()) {
                std::cerr << "Failed to open the file." << std::endl;
                break;
            }

            char value;
            while (codedFile >> value) {
                if (value == '0') {
                    codedMessage.push_back(0);
                } else if (value == '1') {
                    codedMessage.push_back(1);
                } else {
                    std::cerr << "Invalid value in the file." << std::endl;
                    break;
                }
            }
            codedFile.close();

            std::cout << "Zakodowana wiadomosc: ";
            for (const bool v : codedMessage) {
                std::cout << v;
            }
            std::cout << std::endl;

            std::cout << "Wektor bledu: ";
            std::vector<bool> E = algorithm::getErrorVector(codedMessage, doubleErrorMatrix);

            for (const bool v : E) {
                std::cout << v;
            }
            std::cout << std::endl;

            std::vector<bool> correctedMessage = algorithm::detectAndCorrectErrors(codedMessage, doubleErrorMatrix);

            std::cout << "Poprawiona wiadomosc: ";

            for (const bool v : correctedMessage) {
                std::cout << v;
            }
            std::cout << std::endl;

            std::vector<bool> noParityBits = algorithm::removeParityBits(correctedMessage, doubleErrorMatrix);

            std::cout << "Poprawiona wiadomosc bez bitow parzystosci: ";

            for (const bool v : noParityBits) {
                std::cout << v;
            }
            std::cout << std::endl;

            std::string correct = algorithm::binaryToText(noParityBits, doubleErrorMatrix);

            std::cout << "Poprawna wiadomosc: " << correct << std::endl;

            algorithm::restoringDataAfterTransmission(doubleErrorMatrix);

            break;
        }
        default:
            std::cout << "Zly wybor.";
    }

    return 0;
}