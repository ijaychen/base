/*************************************************************************
	> File Name: packet_handler.cpp
	> Author: cjj
	> Created Time: Thu 10 Apr 2014 09:36:30 AM CST
 ************************************************************************/

#include <iostream>
#include <map>
using namespace std;

class Test
{
public:
	void print(int a)
	{
		cout << a << endl;
	}

	void test();
};

struct PacketHandler
{
	PacketHandler(void (Test::*_handler)(int)) : handler(_handler){}
	PacketHandler() : handler(NULL){}
	void (Test::*handler)(int);
};

class PacketHandlerMgr
{
public:
	static PacketHandlerMgr * GetInstance()
	{
		static PacketHandlerMgr _instance;
		return &_instance;
	}

	void AddHandler(int opCodes, void (Test::*_handler)(int))
	{
		map_handler.insert(make_pair(1, PacketHandler(_handler)));
	}

	PacketHandler  GetHandler(int opCode)
	{
		map<int, PacketHandler>::iterator iter = map_handler.find(opCode);
		if(iter != map_handler.end())
		{
			return iter->second;
		}
		else
		{
			return PacketHandler();
		}
	}
private:
	PacketHandlerMgr(){}
	map<int, PacketHandler> map_handler;
};

PacketHandlerMgr * g_handlerMgr = PacketHandlerMgr::GetInstance();

void Test::test()
{

	PacketHandler what_xx = g_handlerMgr->GetHandler(1);
	if(what_xx.handler)
	{
		(this->*what_xx.handler)(46);
	}
}


int main()
{
	g_handlerMgr->AddHandler(1, &Test::print);
	Test tt;
	tt.test();
	return 0;
}


