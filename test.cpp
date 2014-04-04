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

int main()
{
	cout << sizeof(char) << endl;
	cout << sizeof(short) << endl;
	cout << sizeof(int) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(double) << endl;
	int a = 65;
	put((uint8*)&a, sizeof(a));

	cout << __FILE__ << endl;
	
	cout << __LINE__ << endl;

	return 0;
}
