/*************************************************************************
	> File Name: world_session.h
	> Author: cjj
	> Created Time: Mon 14 Apr 2014 10:37:20 AM CST
 ************************************************************************/
#include "world_session.h"
#include "packet_handler.h"
namespace game_server
{
void WorldSession::Test()
{
	g_handlerMgr->AddHandler(1, &WorldSession::Test_Handler);
	PacketHandler what_xx = g_handlerMgr->GetHandler(1);
	if(what_xx.handler)
	{
		base::WorldPacket pack;
		(this->*what_xx.handler)(pack);
	}
}

}
