#include "stdafx.h"

bool Move::Write(OutputMemoryBitStream& _in) const
{
	mInputState.Write(_in);
	_in.Write(mTimestamp);
	return true;
}

bool Move::Read(InputMemoryBitStream& _in)
{
	mInputState.Read(_in);
	_in.Read(mTimestamp);
	return true;
}

