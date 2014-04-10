/*************************************************************************
	> File Name: world_packet.h
	> Author: cjj
	> Created Time: Thu 10 Apr 2014 10:48:56 AM CST
 ************************************************************************/

#ifndef WORLD_PACKET_H
#define WORLD_PACKET_H

#include "packet_base.h"
namespace base{

class WorldPacket : public Packet_Base
{
public:
	WorldPacket(uint32_t _opCode) : m_opCode(_opCode){}
	WorldPacket(const WorldPacket & pack) 
		: m_opCode(pack.GetOpCode()), Packet_Base(pack)
	{}

	uint32_t GetOpCode() const
	{
		return m_opCode;
	}
	

private:
	uint32_t m_opCode;

};
}
#endif
