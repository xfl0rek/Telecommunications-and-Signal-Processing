#ifndef EXERCISE2_GLOBALS_H
#define EXERCISE2_GLOBALS_H

#include <fstream>
#include <Windows.h>

extern char filename[255];
extern std::ofstream file;
extern std::ifstream file2;
extern char dataBlock[128];
extern char first3Bytes[3];
extern char complementTo255;
extern char sign;
extern unsigned long sizeOfSign;
extern int numOfSigns;
extern bool connection;
extern bool isCorrectPacket;
extern int packetNum;
extern char errorControlSum[2];
extern USHORT tmpCRC;
extern bool isCRC;

#endif //EXERCISE2_GLOBALS_H
