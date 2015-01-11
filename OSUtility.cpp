//
//  OSUtility.cpp
//  Assembler
//
//  Created by GregMac on 1/6/15.
//  Copyright (c) 2015 Mac. All rights reserved.
//

#include "OSUtility.h"
#include <iostream>
#include <fstream>



void HexUtility::WriteAsciiToHexIntoFile(char* fname, char* data)
{
    WriteAsciiToHexIntoFile(std::string(fname), std::string(data));
}

void HexUtility::WriteAsciiToHexIntoFile(std::string fname, std::string data)
{
    std::ofstream os (fname);
    if(!os)
        throw std::runtime_error("Error in opening file: "+fname);
    
    for(int i =0; i < data.size();++i)
    {
        BinaryUnit bu;
        bu.ascii = data[i];
        os<<std::hex<<bu.hex.upper<<bu.hex.lower;

    }
    os.flush();
    os.close();
}


std::string HexUtility::ConvertAsciiToHex(char* data)
{
    return ConvertAsciiToHex(std::string(data));
}

std::string HexUtility::ConvertAsciiToHex(std::string data)
{
    std::stringstream buff;
    buff.flags(std::ios::hex);
    for(int i =0; i < data.size();++i)
    {
        buff<<(uint)data[i];
        std::cout<<buff.str()<<std::endl;
    }
    return buff.str();
}

std::string HexUtility::ConvertHexToAscii(char* data)
{
    return ConvertHexToAscii(std::string(data));
}

std::string HexUtility::ConvertHexToAscii(std::string data)
{
    std::stringstream buff(std::ios::hex);
    std::stringstream output;
    
    while(data.size() >0)
    {
        if(data.size()>1)
        {
            output<<SingleCharFromHex(data.substr(0,2));
            data = data.substr(2);
        }
        else
        {
            output<<SingleCharFromHex(data.substr(0,1));
            data = "";
        }
    }
    
    return output.str();
}

char HexUtility::SingleCharFromHex(std::string h)
{
    if(h.size() == 1)
    {
        return HexToDec(h[0]);
    }
    else if(h.size() == 2)
    {
        uint i =HexToDec(h[0]);
        i <<= 4;
        i |= HexToDec(h[1]);
        return (char)i;
    }
    else
    {
        throw std::runtime_error("cannot parse hex " + h + " to a char");
    }
}

int HexUtility::HexToDec(char h)
{
    uint i = (uint)h;
    if(i<58)  //implicit casts
        return i - 48;
    else
        return i - 55;
}

char HexUtility::DecToHex(int i)
{
    if(i<10)  //implicit casts
        return (char)(i + 48);
    else
        return (char)(i + 55);
}

char HexUtility::DecToHex(char c)
{
    int i = (int)c;
    if(i<10)  //implicit casts
        return (char)(i + 48);
    else
        return (char)(i + 55);
}

void HexUtility::WriteHextoAsciiIntoFile(char* fname, char* data)
{
    WriteAsciiToHexIntoFile(std::string(fname), std::string(data));
}

void HexUtility::WriteHextoAsciiIntoFile(std::string fname, std::string data)
{
    std::ofstream os = std::ofstream(fname);
    os<<ConvertHexToAscii(data)<<std::flush;
    os.close();
}

std::string HexUtility::ReadBinaryFileAsHex(char* fname)
{
    return ReadBinaryFileAsHex(std::string(fname));
}

std::string HexUtility::ReadBinaryFileAsHex(std::string fname)
{
    BinaryUnit bu;
    std::stringstream ss;
    
    std::ifstream is = std::ifstream(fname);
    is>>bu.ascii;
    while(!is.eof())
    {
        ss<<bu.hex.upper;
        ss<<bu.hex.lower;
        is>>bu.ascii;
        
    }
    return ss.str();
}

std::string HexUtility::ReadHexFileAsBinary(char* fname)
{
    return ReadHexFileAsBinary(std::string(fname));

}

std::string HexUtility::ReadHexFileAsBinary(std::string fname)
{
    BinaryUnit bu;
    char upper;
    char lower;
    std::stringstream ss;
    
    std::ifstream is = std::ifstream(fname);
    is>>upper;
    while(!is.eof())
    {
        is>>lower;
        if(is.eof())
        {
            bu.hex.lower = HexToDec(upper);
            ss<<bu.ascii;
        }
        else
        {
            bu.hex.lower = HexToDec(lower);
            bu.hex.upper = HexToDec(upper);
            ss<<bu.ascii;
            is>>upper;
        }
    }
    
    return ss.str();
}