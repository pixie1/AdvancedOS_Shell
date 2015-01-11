//
//  OSUtility.h
//  Assembler
//
//  Created by GregMac on 1/6/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#ifndef __Assembler__OSUtility__
#define __Assembler__OSUtility__

#include <sstream>
#include <algorithm>

struct HexByte
{
    uint lower:4;
    uint upper:4;
};

union BinaryUnit
{
    unsigned char ascii;
    HexByte hex;
};

class HexUtility
{
private:
    char SingleCharFromHex(std::string);
    int HexToDec(char);
    char DecToHex(int);
    char DecToHex(char);
    
public:
    
    void WriteAsciiToHexIntoFile(char* fname, char* data);
    void WriteAsciiToHexIntoFile(std::string fname, std::string data);
    std::string ConvertAsciiToHex(char* data);
    std::string ConvertAsciiToHex(std::string data);
    std::string ConvertHexToAscii(char *);
    std::string ConvertHexToAscii(std::string);
    void WriteHextoAsciiIntoFile(char* fname, char* data);
    void WriteHextoAsciiIntoFile(std::string fname, std::string data);
    std::string ReadBinaryFileAsHex(char* fname);
    std::string ReadBinaryFileAsHex(std::string fname);
    std::string ReadHexFileAsBinary(char* fname);
    std::string ReadHexFileAsBinary(std::string fname);
    
};

#endif /* defined(__Assembler__OSUtility__) */
