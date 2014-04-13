/*************************************************************************
	> File Name: packet_buffer.h
	> Author: cjj
	> Created Time: Fri 11 Apr 2014 09:47:31 AM CST
 ************************************************************************/

#ifndef PACKET_BUFFER_H
#define PACKET_BUFFER_H

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "global.h"
namespace game_server
{
const static int MAX_BUFFER_SIZE = 1024 * 512;
const static int DEFAULT_BUFFER_SIZE = 1024 * 2;
class Packet_Buffer
{
public:
	Packet_Buffer(int _socket, size_t _nBufferSize = DEFAULT_BUFFER_SIZE) 
		: m_nSocket(_socket), m_nBufferSize(_nBufferSize), m_nFreeSize(_nBufferSize),
		  m_nBeginPos(0), m_nEndPos(0)
	{
		assert(m_nBufferSize <= MAX_BUFFER_SIZE);
		m_pBuffer = new char[m_nBufferSize];
	}

public:
	bool DoubleSize()
	{
		char * pTemp = m_pBuffer;
		assert(2 * m_nBufferSize <= MAX_BUFFER_SIZE);
		m_pBuffer = new char[2 * m_nBufferSize];
		if(m_nBeginPos < m_nEndPos)
		{
			memcpy(&m_pBuffer[0], pTemp, m_nEndPos - m_nBeginPos);
			m_nEndPos = m_nEndPos - m_nBeginPos;
		}
		else
		{
			int nTemp = m_nBufferSize - m_nBeginPos;
			memcpy(&m_pBuffer[0], &pTemp[m_nBeginPos], nTemp);
			memcpy(&m_pBuffer[nTemp], &pTemp[0], m_nEndPos);
			m_nEndPos += nTemp;
		}
		m_nBeginPos = 0;
		m_nFreeSize += m_nBufferSize;
		m_nBufferSize *= 2;	
		delete pTemp;
		return true;
	}
	
	bool FillBuffer(const char * src, size_t len)
	{
		if(m_nFreeSize < len)
		{
			if(!DoubleSize())
			{
				return false;
			}
		}
		if(m_nBeginPos >= m_nEndPos)
		{
			memcpy(&m_pBuffer[m_nEndPos], src, len);
			m_nEndPos += len;
		}
		else
		{
			int rightLen = m_nBufferSize - m_nEndPos;
			if(rightLen < len)
			{
				memcpy(&m_pBuffer[m_nEndPos], src, rightLen);
				memcpy(&m_pBuffer[0], &src[rightLen], len - rightLen);
				m_nEndPos = (m_nEndPos + len) % m_nBufferSize;
			}
			else
			{
				memcpy(&m_pBuffer[m_nEndPos], src, len);
				m_nEndPos += len;
			}
		}
		m_nFreeSize -= len;
		return true;
	}
protected:
	size_t m_nBufferSize;
	size_t m_nFreeSize;
	char * m_pBuffer;
	int m_nSocket;

	size_t m_nBeginPos;
	size_t m_nEndPos;
};


class Input_Buffer : public Packet_Buffer
{
public:
	Input_Buffer(int _socket, size_t _bufferSize = DEFAULT_BUFFER_SIZE) 
		: Packet_Buffer(_socket, _bufferSize)
	{
		m_pTempBuffer = new char[m_nBufferSize];
	}

	bool FillInputBuffer()
	{
		memset(m_pTempBuffer, 0, sizeof(m_pTempBuffer));
		int len = read(m_nSocket, m_pTempBuffer, DEFAULT_BUFFER_SIZE/2);
		if(-1 == len || 0 == len)
		{
			//player logout
			return ;
		}
		FillBuffer(m_pTempBuffer, len);
	}

	size_t GetBufferSize() const
	{
		return m_nBufferSize - m_nFreeSize;
	}
	
	uint16_t GetPacketSize() const
	{
		int len = GetBufferSize();
		if(len < 2)
		{
			return 0;
		}
		uint16_t packLen = 0;
		char * dst = reinterpret_cast<char *>(&packLen);
		memcpy(dst, &m_pBuffer[m_nBeginPos], 1);
		printf("dst:%d\n", packLen);
		return packLen;
	}

	bool GetPacket(WorldPacket & pack)
	{
		int len = GetPacketSize();
		if(0 == len)
		{
			return false;
		}
		if(len < GetBufferSize())
		{
			return false;
		}
		return ReadBuffer((char*)&pack, len);
	}

private:
	bool ReadBuffer(char *pack, int len)
	{
		if(m_nBeginPos < m_nEndPos)
		{
			memcpy(pack, &m_pBuffer[m_nBeginPos], len);
		}
		else
		{
			int rightLen = m_nBufferSize - m_nBeginPos;
			if(len <= rightLen)
			{
				memcpy(pack, &m_pBuffer[m_nBeginPos], len);
			}
			else
			{
				memcpy(pack, &m_pBuffer[m_nBeginPos], rightLen);
				memcpy(&pack[rightLen], &m_pBuffer[0], len - rightLen);
			}
		}
		m_nFreeSize += len;
		m_nBeginPos = (m_mBeginPos + len) % m_nBufferSize;
		return true;
	}

private:
	char * m_pTempBuffer;
};

class Output_Buffer : public Packet_Buffer
{
public:
	Output_Buffer(int _socket, size_t _nBufferSize = DEFAULT_BUFFER_SIZE) 
		: Packet_Buffer(_socket, _nBufferSize)
	{

	}

	void FillOutputBuffer(const char * src, size_t len)
	{
		assert(src && 0 != len);
		FillBuffer(src, len);	
	}

	bool SendPacket()
	{
		if(m_nFreeSize == m_nBufferSize)
			return false;
		int rightLen;
		if(m_nBeginPos < m_nEndPos)
		{
			write(m_nSocket, m_pBuffer, m_nBufferSize - m_nFreeSize);
		}
		else
		{
			rightLen = m_nBufferSize - m_nBeginPos;
			write(m_nSocket, &m_pBuffer[m_nBeginPos], rightLen);
			write(m_nSocket, &m_pBuffer[0], m_nEndPos);
		}
		m_nBeginPos = 0;
		m_nEndPos = 0;
		return true;
	}
private:

};

}

#endif
