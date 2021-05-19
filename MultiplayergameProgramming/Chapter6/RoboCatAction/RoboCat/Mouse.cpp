#include "stdafx.h"

Mouse::Mouse()
{
	SetScale(GetScale() * 0.5f);
	SetCollisionRadius(0.25f);
}

bool Mouse::HandleCollisionWithCat(RoboCat* _cat)
{
	return false;
}

uint32_t Mouse::Write(OutputMemoryBitStream& _in, uint32_t _dState)const 
{
	uint32_t ret = 0;
	if (_dState & EMRS_Pose)
	{
		_in.Write((bool)true);
		Vector3 loc = GetLocation();
		_in.Write(loc.x);
		_in.Write(loc.y);

		_in.Write(GetRotation());

		ret |= EMRS_Pose;
	}
	else
	{
		_in.Write((bool)false);
	}

	if (_dState & EMRS_Color)
	{
		_in.Write((bool)true);
		_in.Write(GetColor());
		ret |= EMRS_Color;
	}
	else
		_in.Write((bool)false);
	return ret;
}

void Mouse::Read(InputMemoryBitStream& _in)
{
	bool statebit;

	_in.Read(statebit);
	if (statebit)
	{
		Vector3 loc;
		_in.Read(loc.x);
		_in.Read(loc.y);
		SetLocation(loc);

		float rot;
		_in.Read(rot);
		SetRotation(rot);
	}

	_in.Read(statebit);
	if (statebit)
	{
		Vector3 color;
		_in.Read(color);
		SetColor(color);
	}
}