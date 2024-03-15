#include <iostream>
#include "../include/singleErrorCode.h"
#include "../include/doubleErrorCode.h"
#include "../include/algorithm.h"

int main() {

    for (const auto& row : singleErrorMatrix) {
        for (const bool element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;

    for (const auto& row : doubleErrorMatrix) {
        for (const bool element : row) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }

    std::vector<bool> vector1 = {1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0};
    std::vector<bool> vector2 = {1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0};

    std::vector<bool> result1 = algorithm::multiplyMatrixByVector(singleErrorMatrix, vector1);
    std::vector<bool> result2 = algorithm::multiplyMatrixByVector(doubleErrorMatrix, vector2);

    std::cout << std::endl;

    std::cout << "Result vector:" << std::endl;
    for (const bool value : result1) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Result vector:" << std::endl;
    for (const bool value : result2) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::string text = "dupa";

    std::vector<bool> binary1 = algorithm::textToBinary(text, singleErrorMatrix);
    std::vector<bool> binary2 = algorithm::textToBinary(text, doubleErrorMatrix);

    std::cout << "Text to binary result:" << std::endl;

    for (const bool value : binary1) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::cout << "Text to binary result:" << std::endl;

    for (const bool value : binary2) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    std::vector<bool> parityBits = algorithm::addParityBits(binary2, doubleErrorMatrix);

    std::cout << "Add parity bits result:" << std::endl;

    for (const bool value : parityBits) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    return 0;
}