/*************************************************************************
	> File Name: packet.h
	> Author: cjj
	> Created Time: Tue 01 Apr 2014 05:38:50 PM CST
 ************************************************************************/

#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <string>
#include "packetbase.h"

namespace base
{

class PacketIn : public PacketBase
{
public:
	PacketIn(const std::vector<uint8_t> &rhs)
	{
		m_storage.resize(rhs.size());
		memcpy(&m_storage[0], &rhs[0], GetSize());
	}

	uint16_t GetOpCode()
	{
		SkipTo(0);
		uint16_t val;
		GetByte(reinterpret_cast<char*>(&val), 2);
		return val;
	}

	uint16_t PackSize()
	{
		SkipTo(2);
		uint16_t val;
		GetByte(reinterpret_cast<char*>(&val), 2);
		return val;
	}

	uint16_t ReadUShort()
	{
		uint16_t val;
		GetByte(reinterpret_cast<char*>(&val), 2);
		return val;
	}

	void ReadString(std::string &str)
	{
		uint16_t len;
		GetByte(reinterpret_cast<char*>(&len), 2);
		std::cout << "string len: " << len + 0 << std::endl;
		str.resize(len);
		char * dst = const_cast<char*>(str.c_str());
		GetByte(dst, len);
		std::cout << dst << std::endl;
		std::cout << str << std::endl;
	}

	std::string ReadString()
	{
		std::string str;
		ReadString(str);
		return str;
	}

	void GetByte(char * dst, size_t count)
	{
		assert(dst || PrintError(__FILE__, __LINE__));
		assert(m_pos + count <= GetSize() || PrintError(__FILE__, __LINE__));
		memcpy(dst, &m_storage[m_pos], count);
		m_pos += count;
	}

	void test()
	{
		std::vector<uint8_t>::iterator iter = m_storage.begin();
		for(; iter != m_storage.end(); ++iter)
		{
			std::cout << *iter + 0 << " ";
		}
		std::cout << std::endl;
		std::cout << GetOpCode() + 0 << std::endl;
		std::cout << PackSize() + 0 << std::endl;
		std::cout << ReadUShort() << std::endl;
		std::cout << ReadUShort() << std::endl;
		std::cout << ReadString() << std::endl;
	}


};



class PacketOut : public PacketBase
{
public:
	PacketOut(uint16_t code, uint16_t size):PacketBase(code),
		m_headWrite(false)
	{
		m_storage.reserve(size);
		SkipTo(sizeof(uint16_t) + sizeof(uint16_t));
		std::cout << "con-pos: " << m_pos + 0 << std::endl;
	}
	void PutByte(const char * src, size_t count)
	{
		assert(src && 0 != count);
		assert(GetSize() < 10000 || PrintError(__FILE__, __LINE__));

		if((sizeof(m_opCode) + sizeof(uint16_t)) > GetSize())
		{
			m_storage.resize(sizeof(m_opCode) + sizeof(uint16_t) + count);
		}
		if(m_pos + count >  GetSize())
		{
			m_storage.resize(GetSize() +  count);
		}
		memcpy(&m_storage[m_pos], src, count);
		m_pos += count;
	}

	void WriteUShort(uint16_t val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 2);
	}

	void WriteUInt(uint32_t val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 4);
	}

	void WriteInt(int val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 4);
	}

	void WriteFloat(float val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 4);
	}

	void WriteULong(uint64_t val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 8);
	}

	void WriteLong(long val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 8);
	}

	void WriteDouble(double val)
	{
		PutByte(reinterpret_cast<const char *>(&val), 8);
	}

	void WriteString(const char * src)
	{
		uint16_t length = strlen(src);
		PutByte(reinterpret_cast<const char *>(&length), 2);
		PutByte(src, length);
	}

	void WriteHead(bool rewrite = false)
	{
		if(!m_headWrite || rewrite)
		{
			SkipTo(0);
			WriteUShort(GetOpcode());
			WriteUShort(GetSize());
			m_headWrite = true;
		}
	}


	std::vector<uint8_t> FetchData()
	{
		std::vector<uint8_t> data;
		data.resize(GetSize());
		memcpy(&data[0], &m_storage[0], GetSize());
		return data;
	}

	void test()
	{
		std::cout << m_pos + 0 << std::endl;
		std::cout << GetSize() + 0<< std::endl;
		std::vector<uint8_t>::iterator iter = m_storage.begin();
		std::cout << m_storage.size() << std::endl;
		for(; iter != m_storage.end(); ++ iter)
		{
			std::cout << (*iter + 0) << " ";
		}
		std::cout << std::endl;
	}
private:
	bool m_headWrite;

};


}

#endif
