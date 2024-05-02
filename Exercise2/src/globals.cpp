#include "../include/globals.h"

char filename[255];
std::ofstream file;
std::ifstream file2;
char dataBlock[128];
char first3Bytes[3];
char complementTo255;
char sign;
unsigned long sizeOfSign = sizeof(sign);
int numOfSigns = 1;
bool connection = false;
bool isCorrectPacket;
int packetNum;
char errorControlSum[2];
USHORT tmpCRC;
bool isCRC;