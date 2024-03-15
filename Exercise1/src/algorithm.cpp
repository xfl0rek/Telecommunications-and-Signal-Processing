#include "../include/algorithm.h"
#include <iostream>
#include <algorithm>

algorithm::algorithm() = default;

algorithm::~algorithm() = default;

std::vector<bool> algorithm::multiplyMatrixByVector(const std::vector<std::vector<bool>> &matrix,
    const std::vector<bool> &vector) {
    std::vector<bool> result(matrix.size(), 0);

    const size_t rows = matrix.size();

    if (rows == 0) {
        std::cerr << "The matrix is empty" << std::endl;
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
            result[i] = result[i] ^ (matrix[i][j] && vector[j]);
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
    int sum = 0;
    for (int i = 0 ; i < matrix.size(); i++) {
        for (int j = 0; j < matrix.size(); j++) {
            if (matrix[i][j] == 1) {
                sum += text[j];
            }
        }
        if (sum % 2 == 1) {
            text.push_back(1);
        } else {
            text.push_back(0);
        }
    }
    return text;
}

std::vector<bool> algorithm::getErrorVector(std::vector<bool> T, const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> E;

    const int codeWordLength = matrix[0].size();

    for (int wordStartBit = 0; wordStartBit < T.size(); wordStartBit += codeWordLength) {
        std::vector<bool> wordFragment(T.begin() + wordStartBit, T.begin() + wordStartBit + codeWordLength);
        std::vector<bool> result = multiplyMatrixByVector(matrix, wordFragment);
        E.insert(E.end(), result.begin(), result.end());
    }

    return E;
}

std::vector<bool> algorithm::findError(const std::vector<bool>& E, const std::vector<std::vector<bool>>& matrix) {
    std::vector<bool> error;

    std::vector<bool> result = multiplyMatrixByVector(matrix, E);

    for (size_t j = 0; j < matrix[0].size(); j++) {
        std::vector<bool> column;
        for (const auto & i : matrix) {
            column.push_back(i[j]);
        }
        if (result == column) {
            error.push_back(1);
        } else {
            error.push_back(0);
        }
    }

    return error;
}
