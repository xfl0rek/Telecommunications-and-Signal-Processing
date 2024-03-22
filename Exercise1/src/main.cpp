#include <iostream>
#include "../include/singleErrorCode.h"
#include "../include/doubleErrorCode.h"
#include "../include/algorithm.h"

int main() {

    std::string text = "dupa";
    std::vector<bool> message = algorithm::textToBinary(text, doubleErrorMatrix);

    for (const bool value : message) {
        std::cout << value;
    }

    std::cout << std::endl;

    std::vector<bool> addParityBits = algorithm::addParityBits(message, doubleErrorMatrix);

    for (const bool value : addParityBits) {
        std::cout << value;
    }

    std::cout << std::endl;

    std::vector<bool> E = algorithm::getErrorVector(addParityBits, doubleErrorMatrix);

    for (const bool value : E) {
        std:: cout << value;
    }
    std::cout << std::endl;

    algorithm::preparationForTransmission(doubleErrorMatrix);

    std::vector<bool> remove = algorithm::removeParityBits(addParityBits, doubleErrorMatrix);

    for (const bool value : remove) {
        std::cout << value;
    }
    std::cout << std::endl;

    std::string decodedMessage = algorithm::binaryToText(remove, doubleErrorMatrix);

    std::cout << decodedMessage << std::endl;

    return 0;
}