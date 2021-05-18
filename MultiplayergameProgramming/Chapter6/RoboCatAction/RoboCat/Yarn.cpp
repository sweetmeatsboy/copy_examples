#include "stdafx.h"

Yarn::Yarn()
	:mMuzzleSpeed(3.f)
	, mVelocity(Vector3::Zero)
	, mPlayerId(0)
{
	SetScale(GetScale() * 0.25f);
	SetCollisionRadius(0.125f);
}

uint32_t Yarn::Write(OutputMemoryBitStream& _in, uint32_t _dState) const
{
	uint32_t ret = 0;
	if (_dState &  EYRS_Pose)
	{
		_in.Write((bool)true);
		Vector3 loc = GetLocation();
		_in.Write(loc.x);
		_in.Write(loc.y);

		Vector3 vel = GetVelocity();
		_in.Write(vel.x);
		_in.Write(vel.y);

		_in.Write(GetRotation());
		ret |= EYRS_Pose;
	}
	else
		_in.Write((bool)false);

	if (_dState &  EYRS_Color)
	{
		_in.Write((bool)true);
		_in.Write(GetColor());
		ret |= EYRS_Color;
	}
	else
		_in.Write((bool)false);

	if (_dState &  EYRS_PlayerId)
	{
		_in.Write((bool)true);
		_in.Write(mPlayerId, 8);
		ret |= EYRS_PlayerId;
	}
	else
		_in.Write((bool)false);

	return ret;
}

bool Yarn::HandleCollisionWithCat(RoboCat* _cat)
{
	return false;
}

void Yarn::InitFromShooter(RoboCat* _cat) 
{
	SetColor(_cat->GetColor());
	SetPlayerId(_cat->GetPlayerId());

	Vector3 forward = _cat->GetForwardVector();
	Setvelocity(_cat->GetVelocity() + forward * mMuzzleSpeed);
	SetLocation(_cat->GetLocation());

	SetRotation(_cat->GetRotation());
}

void Yarn::Update()
{
	float deltaTime = Timing::sInstance
		.GetDeltaTime(); 
	SetLocation(GetLocation() + mVelocity * deltaTime);
}