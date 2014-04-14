/*************************************************************************
	> File Name: world_session.h
	> Author: cjj
	> Created Time: Mon 14 Apr 2014 10:37:20 AM CST
 ************************************************************************/
#ifndef WORLD_SESSION_H
#define WORLD_SESSION_H
#include <iostream>
#include "world_packet.h"
namespace game_server
{
class WorldSession
{
public:
	void Test_Handler(base::WorldPacket & pack)
	{
		std::cout << "WorldSession\ngood job\n";
	}

	void Test();
};

}

#endif
