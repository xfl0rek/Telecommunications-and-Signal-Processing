#include <cstdint>
#include "../include/utility.h"

int utility::calculateCRC(char *data, int count) {
    uint16_t CRCchecksum = 0;

    while (count-- > 0) {
        CRCchecksum ^= static_cast<uint16_t>(*data++) << 8;
        for (int i = 0; i < 8; ++i) {
            if (CRCchecksum & 0x8000) {
                CRCchecksum = (CRCchecksum << 1) ^ 0x1021;
            } else {
                CRCchecksum <<= 1;
            }
        }
    }

    return CRCchecksum;
}

int utility::calculateChecksum(const char *data) {
    int checksum = 0;
    for (int i = 0; i < 128; i++) {
        checksum += (unsigned char)data[i];
    }
    checksum %= 256;
    return checksum;
}

char utility::calculateCRCByte(int n, int signNum) {
    int binary[16] = {0};

    for (int i = 0; i < 16; ++i) {
        binary[15 - i] = n & (1 << i) ? 1 : 0;
    }

    int sum = 0;
    int k = (signNum == 1) ? 7 : 15;

    for (int i = 0; i < 8; ++i) {
        sum += (1 << i) * binary[k - i];
    }

    return static_cast<char>(sum);
}
