#ifndef ALGORITHM_H
#define ALGORITHM_H
#include <vector>

class algorithm {
public:
    algorithm();
    ~algorithm();
    static std::vector<bool> multiplyMatrixByVector(const std::vector<std::vector<bool>>& matrix,
        const std::vector<bool>& vector);
};

#endif //ALGORITHM_H
