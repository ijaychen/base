/*************************************************************************
	> File Name: global.h
	> Author: cjj
	> Created Time: Fri 21 Mar 2014 09:45:30 AM CST
 ************************************************************************/
#ifndef GLOBAL_H
#define GLOBAL_H

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

#include <iostream>
bool PrintError(const char * fileName, int lineNum)
{
	std::cout << "exception in file: " << fileName << "\tline: " << lineNum << std::endl;
	return false;
}

#endif
