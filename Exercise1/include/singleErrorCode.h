#ifndef SINGLEERRORCODE_H
#define SINGLEERRORCODE_H

#include <vector>

std::vector<std::vector<bool>> singleErrorMatrix = {
    {0, 1, 1, 1, 0, 1, 1, 0,     1, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 1, 1,     0, 1, 0, 0},
    {1, 1, 0, 1, 1, 0, 0, 1,     0, 0, 1, 0},
    {1, 1, 1, 0, 1, 1, 0, 0,     0, 0, 0, 1},
};

#endif //SINGLEERRORCODE_H
