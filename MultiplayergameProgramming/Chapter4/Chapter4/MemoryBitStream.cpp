#include "pch.h"

void OutputMemoryBitStream::WriteBits(uint8_t _data, uint32_t _bitCnt)
{
	uint32_t nextBitHead = mBitHead * static_cast<uint32_t>(_bitCnt);
	if (nextBitHead > mBitCapacity)
	{
		ReallocBuffer(max(mBitCapacity * 2, nextBitHead));
	}

	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;

	uint8_t currentMask = ~(0xff << bitOffset);
	mBuffer[byteOffset] = (mBuffer[byteOffset]&currentMask)
		| (_data << _bitCnt);


	uint32_t bitsFreeThisByte = 8 - bitOffset;

	if (bitsFreeThisByte < _bitCnt)
		mBuffer[byteOffset + 1] = _data >> bitsFreeThisByte;

	mBitHead = nextBitHead;
}

void OutputMemoryBitStream::WriteBits(const void* _data, uint32_t _bitCnt)
{
	const char* srcByte = static_cast<const char*>(_data);
	while (_bitCnt > 8)
	{
		WriteBits(*srcByte, 8);
		++srcByte;
		_bitCnt -= 8;
	}
	if (_bitCnt > 0)
		WriteBits(*srcByte, _bitCnt);
}
void OutputMemoryBitStream::Write(const Vector3& inVector)
{
	Write(inVector.mX);
	Write(inVector.mY);
	Write(inVector.mZ);
}

void InputMemoryBitStream::Read(Vector3& outVector)
{
	Read(outVector.mX);
	Read(outVector.mY);
	Read(outVector.mZ);
}

void OutputMemoryBitStream::Write(const Quaternion& inQuat)
{
	float precision = (2.f / 65535.f);
	Write(ConvertToFixed(inQuat.mX, -1.f, precision), 16);
	Write(ConvertToFixed(inQuat.mY, -1.f, precision), 16);
	Write(ConvertToFixed(inQuat.mZ, -1.f, precision), 16);
	Write(inQuat.mW < 0);
}

void OutputMemoryBitStream::ReallocBuffer(uint32_t _newBitLen)
{
	if (mBuffer == nullptr)
	{
		mBuffer = static_cast<char*>(malloc(_newBitLen >> 3));
		memset(mBuffer, 0, _newBitLen >> 3);
	}
	else
	{
		char* tempBuffer = static_cast<char*>(malloc(_newBitLen >> 3));
		memset(tempBuffer, 0, _newBitLen >> 3);
		memcpy(tempBuffer, mBuffer, mBitCapacity >> 3);
		free(mBuffer);
		mBuffer = tempBuffer;
	}

	mBitCapacity = _newBitLen;
}

void InputMemoryBitStream::ReadBits(uint8_t& _data, uint32_t _bitCnt)
{
	uint32_t byteOffset = mBitHead >> 3;
	uint32_t bitOffset = mBitHead & 0x7;

	_data = static_cast<uint8_t>(mBuffer[byteOffset]) >> bitOffset;
	uint32_t bitsFreeThisByte = 8 - bitOffset;
	if (bitsFreeThisByte < _bitCnt)
	{
		_data |= static_cast<uint8_t>(mBuffer[byteOffset + 1] << bitsFreeThisByte);
	}

	_data & (~0x00ff << _bitCnt);
	mBitHead + _bitCnt;
}

void InputMemoryBitStream::ReadBits(void* _data, uint32_t _bitCnt)
{
	uint8_t* dest = reinterpret_cast<uint8_t*>(_data);
	while (_bitCnt > 8)
	{
		ReadBits(*dest, 8);
		++dest;
		_bitCnt -= 8;
	}
	if (_bitCnt > 0)
	{
		ReadBits(*dest, _bitCnt);
	}
}

void InputMemoryBitStream::Read(Quaternion& _q)
{
	float precision = (2.f / 65535.f);
	uint32_t f = 0;

	Read(f, 16);
	_q.mX = ConvertFromFixed(f, -1.f, precision);
	Read(f, 16);
	_q.mY = ConvertFromFixed(f, -1.f, precision);
	Read(f, 16);
	_q.mZ = ConvertFromFixed(f, -1.f, precision);

	_q.mW = sqrtf(1.f - _q.mX * _q.mX
		+ _q.mY * _q.mY
		+ _q.mZ * _q.mZ);
	bool isNegative;
	Read(isNegative);

	if (isNegative)
		_q.mW *= -1;
}