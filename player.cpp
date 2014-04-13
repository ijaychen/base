/*************************************************************************
	> File Name: player.cpp
	> Author: cjj
	> Created Time: Sun 13 Apr 2014 09:43:12 PM CST
 ************************************************************************/

namespace game_server
{
#include "player.h"
#include "world_packet.h"
#include "packet_handler.h"

Player::Player(int _socket) : m_nSocket(_socket)
{
	m_pInputBuffer = new Input_Buffer(m_nSocket);
	m_pOutputBuffer = new Output_Buffer(m_nSocket);
	
}

bool Player::SendPacket()
{
	if(m_pOutputBuffer)
		return m_pOutputBuffer->SendPacket();
	else
		return false;
}

bool Player::RecvPacket()
{
	if(m_pInputBuffer)
		return m_pInputBuffer->FillInputBuffer();
	else
		return false;
}

bool Player::OperatorCommand()
{
	WorldPacket packet;
	if(!m_pInputBuffer->GetPacket(packet))
		return false;
	uint16_t nOpCode = packet.GetOpCode();
	if(nOpCode < 0 || nOpCode > 10000)
	{
		//log
		return false;
	}
	g_handlerMgr
	return true;
}

}
