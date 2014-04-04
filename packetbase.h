/*************************************************************************
	> File Name: packetBuffer.h
	> Author: cjj
	> Created Time: Fri 21 Mar 2014 09:40:42 AM CST
 ************************************************************************/

#ifndef PACKET_BUFFER_H
#define PACKET_BUFFER_H

#include "global.h"
#include <vector>
#include <assert.h>
#include <string.h>

namespace base{

class PacketBase
{
public:
	PacketBase(uint16_t code = 0)
		:m_opCode(code), m_pos(0){}
	//virtual PacketBase(const PacketBase & ) = 0;
	void SkipTo(size_t pos)
	{
		m_pos = pos;
	}

	uint16_t GetOpcode() const
	{
		return m_opCode;
	}

	uint16_t GetSize() const 
	{
		return m_storage.size();
	}
private:
	PacketBase & operator=(const PacketBase &);
protected:
	uint8_t m_pos;
	uint16_t m_opCode;
	std::vector<uint8_t> m_storage;

};

}
#endif
