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

    const size_t colums = matrix[0].size();

    if (colums != vector.size()) {
        std::cerr << "Invalid matrix and vector sizes." << std::endl;
        return {};
    }

    std::vector<bool> size(rows, 0);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < colums; ++j) {
            result[i] = result[i] || (matrix[i][j] && vector[j]);
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
        std::transform(matrix.begin(), matrix.end(), std::back_inserter(E),
            [&](const std::vector<bool>& row) {
            int result = 0;
            for (int i = 0; i < codeWordLength; i++) {
                result += T[wordStartBit + i] * row[i];
            }
            return result % 2;
        });
    }
    return E;
}