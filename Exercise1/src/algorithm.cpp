#include "../include/algorithm.h"
#include <iostream>
#include <algorithm>
#include <fstream>

algorithm::algorithm() = default;

algorithm::~algorithm() = default;

std::vector<bool> algorithm::multiplyMatrixByVector(const std::vector<std::vector<bool>> &matrix,
    const std::vector<bool> &vector) {
    std::vector<bool> result(matrix.size(), 0);

    const size_t rows = matrix.size();

    if (rows == 0) {
        std::cerr << "The matrix is empty." << std::endl;
        return {};
    }

    const size_t columns = matrix[0].size();

    if (columns != vector.size()) {
        std::cerr << "Invalid matrix and vector sizes." << std::endl;
        return {};
    }

    std::vector<bool> size(rows, 0);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < columns; ++j) {
            result[i] = result[i] ^ (matrix[i][j] & vector[j]);
        }
    }

    return result;
}

std::vector<bool> algorithm::textToBinary(const std::string& text,
    const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> result;
    const int size = matrix.size();
    for (const char character : text) {
        for (int j = size - 1; j >= 0; j--) {
            result.push_back((character >> j) & 1);
        }
    }
    return result;
}

std::vector<bool> algorithm::addParityBits(std::vector<bool> text, const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> result;
    std::vector<std::vector<bool>> subMatrix;

    size_t subMatrixSize = matrix.size();
    for (size_t i = 0; i < subMatrixSize; ++i) {
        std::vector<bool> row;
        for (size_t j = 0; j < subMatrixSize; ++j) {
            row.push_back(matrix[i][j]);
        }
        subMatrix.push_back(row);
    }

    for (size_t i = 0; i < text.size(); i += matrix.size()) {
        std::vector<bool> subText(text.begin() + i, text.begin() + i + matrix.size());

        std::vector<bool> parityBits = multiplyMatrixByVector(subMatrix, subText);

        result.insert(result.end(), subText.begin(), subText.end());
        result.insert(result.end(), parityBits.begin(), parityBits.end());
    }

    return result;
}

std::vector<bool> algorithm::getErrorVector(std::vector<bool> T, const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> E;

    for (size_t i = 0; i < T.size(); i += matrix[0].size()) {
        std::vector<bool> wordFragment(T.begin() + i, T.begin() + i + matrix[0].size());
        std::vector<bool> result = multiplyMatrixByVector(matrix, wordFragment);
        E.insert(E.end(), result.begin(), result.end());
    }

    return E;
}

std::vector<bool> algorithm::detectAndCorrectErrors(std::vector<bool> &message, const std::vector<std::vector<bool> > &matrix) {
    std::vector<bool> detectedErrors = getErrorVector(message, matrix);

    bool errorDetected = std::any_of(detectedErrors.begin(), detectedErrors.end(), [](bool val) { return val; });

    if (errorDetected) {
        for (size_t i = 0; i < matrix[0].size(); ++i) {
            bool isCorrect = true;
            for (size_t j = 0; j < matrix.size(); ++j) {
                if (matrix[j][i] != detectedErrors[j]) {
                    isCorrect = false;
                    break;
                }
            }
            if (isCorrect) {
                message[i] = !message[i];
                return message;
            }
        }

        for (size_t i = 0; i < matrix[0].size() - 1; ++i) {
            for (size_t j = i + 1; j < matrix[0].size(); ++j) {
                bool isCorrect = true;
                for (size_t k = 0; k < matrix.size(); ++k) {
                    if ((matrix[k][i] ^ matrix[k][j]) != detectedErrors[k]) {
                        isCorrect = false;
                        break;
                    }
                }
                if (isCorrect) {
                    message[i] = !message[i];
                    message[j] = !message[j];
                    return message;
                }
            }
        }
    }

    return message;
}

void algorithm::preparationForTransmission(const std::vector<std::vector<bool>>& matrix) {
    std::fstream file("../message.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    std::string message;
    if (!std::getline(file, message)) {
        std::cerr << "Failed to read the message." << std::endl;
        file.close();
        return;
    }

    file.close();

    std::vector<bool> msg = textToBinary(message, matrix);
    std::vector<bool> codedMessage = addParityBits(msg, matrix);

    std::fstream codedFile("../codedMessage.txt");
    if (!codedFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    for (auto&& i : codedMessage) {
        codedFile << i;
    }

    codedFile.close();
}

std::string algorithm::binaryToText(const std::vector<bool>& binary, const std::vector<std::vector<bool>>& matrix) {
    std::string result;
    const int size = matrix.size();
    std::vector<bool> currentCharBits;

    for (const bool i : binary) {
        currentCharBits.push_back(i);
        if (currentCharBits.size() == size) {
            char character = 0;
            for (size_t j = 0; j < currentCharBits.size(); ++j) {
                character |= currentCharBits[j] << (size - 1 - j);
            }
            result += character;
            currentCharBits.clear();
        }
    }
    return result;
}

std::vector<bool> algorithm::removeParityBits(std::vector<bool> text, const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> result;

    for (size_t i = 0; i < text.size(); i += matrix[0].size()) {
        for (size_t j = 0; j < matrix.size(); j++) {
            result.push_back(text[i + j]);
        }
    }
    return result;
}

void algorithm::restoringDataAfterTransmission(const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> codedMessage;

    std::fstream codedFile("../codedMessage.txt");
    if (!codedFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return;
    }

    char value;
    while (codedFile >> value) {
        if (value == '0') {
            codedMessage.push_back(0);
        } else if (value == '1') {
            codedMessage.push_back(1);
        } else {
            std::cerr << "Invalid value in the file." << std::endl;
            return;
        }
    }
    codedFile.close();

    std::vector<bool> correctedMessage = detectAndCorrectErrors(codedMessage, matrix);
    std::vector<bool> remove = removeParityBits(correctedMessage, matrix);
    std::string decodedMessage = binaryToText(remove, matrix);

    std::fstream decodedFile("../decodedMessage.txt");
    if (decodedFile.is_open()) {
        decodedFile << decodedMessage;
    } else {
        std::cout << "Failed to open the file.";
    }
    decodedFile.close();
}