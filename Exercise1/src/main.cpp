#include <iostream>
#include "../include/singleErrorCode.h"
#include "../include/doubleErrorCode.h"
#include "../include/algorithm.h"

int main() {
    //algorithm::preparationForTransmission(doubleErrorMatrix);

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

    std::vector<bool> remove = algorithm::removeParityBits(message, doubleErrorMatrix);

    for (const bool value : remove) {
        std::cout << value;
    }
    std::cout << std::endl;

    std::string decodedText = algorithm::binaryToText(remove, doubleErrorMatrix);

    std::cout << decodedText;

    return 0;
}