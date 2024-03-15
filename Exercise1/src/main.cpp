#include <iostream>
#include "../include/singleErrorCode.h"
#include "../include/doubleErrorCode.h"

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

    return 0;
}