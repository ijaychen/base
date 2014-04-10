/*************************************************************************
	> File Name: packet_base.cpp
	> Author: cjj
	> Created Time: Thu 10 Apr 2014 11:20:53 AM CST
 ************************************************************************/

#include "packet_base.h"
#include <iostream>
using namespace std;
int main()
{
	base::Packet_Base pack;
	pack.WriteUInt(1234);
	pack.WriteUInt(2345);
	base::Packet_Base packIn(pack);
	cout << packIn.ReadUInt() << endl; 
	cout << packIn.ReadUInt() << endl;
	return 0;
}
