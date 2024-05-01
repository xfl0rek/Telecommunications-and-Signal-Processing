#ifndef EXERCISE2_UTILITY_H
#define EXERCISE2_UTILITY_H

#include <iostream>

class utility {
public:
    static int calculateCRC(char* data, int count);
    static int calculateChecksum(const char* data);
    static char calculateCRCByte(int n, int signNum);
};

#endif //EXERCISE2_UTILITY_H
