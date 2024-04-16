#include <iostream>
#include "../include/matrix.h"
#include "../include/algorithm.h"

int main() {
    int choice;

    std::cout << "Choose an option:" << std::endl;
    std::cout << "1. Encode the message." << std::endl;
    std::cout << "2. Decode the message." << std::endl;
    std::cin >> choice;

    switch (choice) {
        case 1: {
            algorithm::preparationForTransmission(matrix);
            break;
        }
        case 2: {
            algorithm::restoringDataAfterTransmission(matrix);
            break;
        }
        default:
            std::cout << "Wrong choice.";
    }

    return 0;
}