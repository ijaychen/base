/*************************************************************************
	> File Name: packet_base.h
	> Author: cjj
	> Created Time: Thu 10 Apr 2014 10:52:15 AM CST
 ************************************************************************/

#ifndef PACKET_BASE_H
#define PACKET_BASE_H

#include <iostream>
#include <assert.h>
#include <string.h>
#include <vector>
#include "global.h"
namespace base{

class Packet_Base
{
public:
	Packet_Base(size_t size = 0x1000) : m_pos(0)
	{
		m_storage.reserve(size);
	}

	Packet_Base(const Packet_Base & rhs) : m_storage(rhs.m_storage), m_pos(0){}
	void WriteUInt(uint32_t val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 4);
	}


	uint32_t ReadUInt()
	{
		uint32_t val;
		GetByte(reinterpret_cast<char*>(&val), 4);
		return val;
	}

	
private:
	void PutByte(const char * src, size_t count)
	{
		if(m_pos + count > m_storage.size())
		{
			m_storage.resize(m_pos + count);
		}
		memcpy(&m_storage[m_pos], src, count);
		m_pos += count;

	}

	void GetByte(char * dst, size_t count)
	{
		assert(m_pos + count <= m_storage.size());
		memcpy(dst, &m_storage[m_pos], count);
		m_pos += count;
	}

private:
	std::vector<uint8_t> m_storage;
	size_t m_pos;

};
}
#endif

