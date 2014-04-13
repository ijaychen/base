/*************************************************************************
	> File Name: pack_test.cpp
	> Author: cjj
	> Created Time: Wed 02 Apr 2014 02:10:17 PM CST
 ************************************************************************/
#include "packet.h"

int main()
{
	base::PacketOut PkOut(1, 10);
	PkOut.WriteUShort(65535);
	PkOut.WriteUShort(66);
	PkOut.WriteString("Hello World");
	PkOut.WriteHead();
	PkOut.test();

	std::cout << "-----------------------------------------\n";

	base::PacketIn PkIn(PkOut.FetchData());
	PkIn.test();

	std::cout << sizeof(base::PacketOut) << std::endl;
	std::cout << sizeof(base::PacketIn) << std::endl;
	return 0;
}
