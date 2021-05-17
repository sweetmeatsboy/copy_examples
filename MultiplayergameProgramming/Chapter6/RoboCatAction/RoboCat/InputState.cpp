#include "stdafx.h"

namespace {
	void WriteSignedBinaryValue(OutputMemoryBitStream& _in, float _val)
	{
		bool isNonZero = (_val != 0.f);
		_in.Write(isNonZero);
		if (isNonZero)
			_in.Write(_val > 0.f);
	}

	void ReadSignedBinaryValue(InputMemoryBitStream& _in, float& _val)
	{
		_val = 0.f;
		bool isNonZero;
		_in.Read(isNonZero);
		if (isNonZero)
		{
			bool isPositive;
			_in.Read(isPositive);
			_val = isPositive ? 1.f : -1.f;
		}
	}
}

bool InputState::Write(OutputMemoryBitStream& _in) const
{
	WriteSignedBinaryValue(_in, GetDesiredHorizontalDelte());
	WriteSignedBinaryValue(_in, GetDesiredVerticalDelta());
	_in.Write(mIsShooting);
	return false;
}

bool InputState::Read(InputMemoryBitStream& _in)
{
	ReadSignedBinaryValue(_in, mDesiredRightAmount);
	ReadSignedBinaryValue(_in, mDesiredForwardAmount);
	_in.Read(mIsShooting);
	return true;
}