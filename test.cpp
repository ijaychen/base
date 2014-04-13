/*************************************************************************
	> File Name: test.cpp
	> Author: cjj
	> Created Time: Fri 21 Mar 2014 10:03:32 AM CST
 ************************************************************************/
#include <iostream>
#include <vector>
#include <string.h>

using std::cout;
using std::endl;
typedef unsigned char uint8;
std::vector<uint8> vec;

void put(uint8 *src, int count)
{
	vec.reserve(1024);
	//vec.insert((uint8)'1');
	memcpy(&vec[0], src, count);
	std::vector<uint8>::iterator iter = vec.begin();
	for(; iter != vec.end(); ++iter)
	{
		cout << *iter;
	}
	cout << &vec[0] << endl;
}

#include "packet_buffer.h"

int main()
{
	game_server::Input_Buffer pb(3);
	pb.FillBuffer("ab", 2);
	cout << pb.GetBufferSize() << endl;
	cout << "packet size: " << pb.GetPacketSize() << endl;
	return 0;
}
