#include "pch.h"

void OutputMemoryStream::ReallocBuffer(uint32_t _newLine)
{
	mBuffer = static_cast<char*>(realloc(mBuffer, _newLine));
	mCapacity = _newLine;
}

void OutputMemoryStream::Write(const void* _data, size_t _byteCnt)
{
	uint32_t ret = mHead + static_cast<uint32_t>(_byteCnt);
	if (ret > mCapacity)
		ReallocBuffer(max(mCapacity * 2, ret));

	memcpy(mBuffer + mHead, _data, _byteCnt);
	mHead = ret;
}

void InputMemoryStream::Read(void* _data, uint32_t _byteCnt)
{
	uint32_t ret = mHead + _byteCnt;
	if (ret > mCapacity)
	{
	}

	memcpy(_data, mBuffer + mHead, _byteCnt);
	mHead = ret;
}