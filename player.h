/*************************************************************************
	> File Name: player.h
	> Author: cjj
	> Created Time: Sun 13 Apr 2014 09:40:23 PM CST
 ************************************************************************/

#ifndef PLAYER_H
#define PLAYER_H

namespace game_server
{
class Player
{
public:
	Player(int _socket);

private:
	int m_nSocket;
};

}
#endif
