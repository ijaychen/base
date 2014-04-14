/*************************************************************************
	> File Name: player.h
	> Author: cjj
	> Created Time: Sun 13 Apr 2014 09:40:23 PM CST
 ************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

namespace game_server
{

class Input_Buffer;
class OutPut_Buffer;

class Player
{
public:
	Player(int _socket);

	bool RecvPacket();
	bool SendPacket();

	bool OperatorCommand();

private:
	unsigned int m_nPlayerId;
	int m_nSocket;
	Input_Buffer * m_pInputBuffer;
	OutPut_Buffer * m_pOutputBuffer;
	
};

}
#endif
