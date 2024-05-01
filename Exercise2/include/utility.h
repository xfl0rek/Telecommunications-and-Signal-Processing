#ifndef EXERCISE2_UTILITY_H
#define EXERCISE2_UTILITY_H

#include <iostream>

class utility {
public:
    static int calculateCRC(char* data, int count);
    int calculateChecksum(char* data);
};

#endif //EXERCISE2_UTILITY_H
