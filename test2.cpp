/*************************************************************************
	> File Name: packet_base.cpp
	> Author: cjj
	> Created Time: Thu 10 Apr 2014 11:20:53 AM CST
 ************************************************************************/

#include "packet_base.h"
#include "world_packet.h"
#include <iostream>
using namespace std;
int main()
{
	base::WorldPacket pack(1);
	pack.WriteUInt(1234);
	pack.WriteUInt(2345);
	pack.WriteString("Hello World");
	base::WorldPacket packIn(pack);
	cout << packIn.GetOpCode() << endl;
	cout << packIn.ReadUInt() << endl; 
	cout << packIn.ReadUInt() << endl;
	cout << packIn.ReadString() << endl;
	return 0;
}
