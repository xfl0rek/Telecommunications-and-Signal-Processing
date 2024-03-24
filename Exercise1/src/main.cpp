#include <iostream>
#include "../include/doubleErrorCode.h"
#include "../include/algorithm.h"
#include <fstream>

int main() {
    int choice;

    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Encode the message." << std::endl;
    std::cout << "2. Decode the message." << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            algorithm::preparationForTransmission(doubleErrorMatrix);
            break;
        }
        case 2: {
            algorithm::restoringDataAfterTransmission(doubleErrorMatrix);
            break;
        }
        default:
            std::cout << "Wrong choice.";
    }

    return 0;
}