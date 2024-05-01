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