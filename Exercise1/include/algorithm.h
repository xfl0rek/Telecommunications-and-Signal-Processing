#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <string>
#include <vector>

class algorithm {
public:
    algorithm();
    ~algorithm();
    static std::vector<bool> multiplyMatrixByVector(const std::vector<std::vector<bool>>& matrix,
        const std::vector<bool>& vector);
    static std::vector<bool> textToBinary(const std::string& text,
        const std::vector<std::vector<bool>>& matrix);
    static std::vector<bool> addParityBits(std::vector<bool> text, const std::vector<std::vector<bool>>& matrix);
};

#endif //ALGORITHM_H
