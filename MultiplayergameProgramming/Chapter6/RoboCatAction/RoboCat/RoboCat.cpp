#include "stdafx.h"

const float HALF_WORLD_HEIGHT = 3.6f;
const float HALF_WORLD_WIDTH = 6.4f;

RoboCat::RoboCat()
	: GameObject()
	, mMaxRotationSpeed(5.f)
	, mVelocity(50.f)
	, mWallRestitution(0.1f)
	, mCatRestitution(0.1f)
	, mThrustDir(0.f)
	, mPlayerId(0)
	, mIsShooting(false)
	, mHealth(10)
{
	SetCollisionRadius(0.5f);
}


void RoboCat::ProcessInput(float _deltaTime, const InputState& _state)
{
	float newRot = GetRotation() + _state.GetDesiredHorizontalDelte() 
		* mMaxRotationSpeed * _deltaTime;

	SetRotation(newRot);

	float inputForwardDelta = _state.GetDesiredVerticalDelta();
	mThrustDir = inputForwardDelta;

	mIsShooting = _state.IsShooting();
}

void RoboCat::AdjustVelocityByThrust(float _delta)
{
	Vector3 fVec = GetForwardVector();
	mVelocity = fVec * (mThrustDir * _delta * mMaxLinearSpeed);
}

void RoboCat::SimulateMovement(float _deltaTime)
{
	AdjustVelocityByThrust(_deltaTime);
	SetLocation(GetLocation() + mVelocity * _deltaTime);
	ProcessCollisions();
}

void RoboCat::Update()
{
}

void RoboCat::ProcessCollisions()
{
	ProcessCollisionsWithScreenWalls();

	float sourceRadius = GetCollisionRadius();
	Vector3 loc = GetLocation();

	for (auto golt = World::sInstance->GetGameObjects().begin()
		, end = World::sInstance->GetGameObjects().end(); golt!= end; ++golt)
	{
		GameObject* target = golt->get();
		if (target == this)
			continue;
		if (target->DoesWantToDie())
			continue;

		Vector3 tLoc = target->GetLocation();
		float tRadius = target->GetCollisionRadius();

		Vector3 delta = tLoc - loc;
		float distSq = delta.LenSq2D();
		float collisionDist = (sourceRadius + tRadius);
		if (distSq >= (collisionDist * collisionDist))
			continue;

		if (target->HandleCollisionWithCat(this) == false)
			continue;
		Vector3 dirToTarget = delta;
		dirToTarget.Normalize2D();
		Vector3 acceptableDeltaFromSourceToTarget = dirToTarget * collisionDist;
		SetLocation(tLoc - acceptableDeltaFromSourceToTarget);

		Vector3 relVel = mVelocity;

		RoboCat* tCat = target->GetAsCat();
		if (tCat != nullptr)
			relVel -= tCat->mVelocity;
		float relVelDotDir = Dot2D(relVel, dirToTarget);

		if (relVelDotDir > 0.f)
		{
			Vector3 impulse = relVelDotDir * dirToTarget;
			if (tCat != nullptr)
			{
				mVelocity -= impulse;
				mVelocity *= mCatRestitution;
			}
			else
			{
				mVelocity -= impulse;
				mVelocity *= mWallRestitution;
			}
		}
	}
}

void RoboCat::ProcessCollisionsWithScreenWalls()
{
	Vector3 loc = GetLocation();
	float x = loc.x;
	float y = loc.y;

	float vx = mVelocity.x;
	float vy = mVelocity.y;

	float radius = GetCollisionRadius();

	if(y + radius >= HALF_WORLD_HEIGHT && vy > 0)
	{
		mVelocity.y = -vy * mWallRestitution;
		loc.y = HALF_WORLD_HEIGHT - radius;
		SetLocation(loc);
	}
	else if (y <= (-HALF_WORLD_HEIGHT - radius) && vy < 0)
	{
		mVelocity.y = -vy * mWallRestitution;
		loc.y = -HALF_WORLD_HEIGHT - radius;
		SetLocation(loc);
	}
	
	if ((x + radius) >= HALF_WORLD_WIDTH && vx > 0)
	{
		mVelocity.x = -vx * mWallRestitution;
		loc.x = HALF_WORLD_WIDTH - radius;
		SetLocation(loc);
	}
	else if (x <= (-HALF_WORLD_WIDTH - radius) && vx < 0)
	{
		mVelocity.x = -vx * mWallRestitution;
		loc.x = -HALF_WORLD_WIDTH - radius;
		SetLocation(loc);
	}
}

uint32_t RoboCat::Write(OutputMemoryBitStream& _in, uint32_t _dState) const
{
	uint32_t wState = 0;
	if (_dState & ECRS_PlayerId)
	{
		_in.Write((bool)true);
		_in.Write(GetPlayerId());
		wState |= ECRS_PlayerId;
	}
	else
		_in.Write((bool)false);

	if (_dState & ECRS_Pose)
	{
		_in.Write((bool)true);
		Vector3 vel = mVelocity;
		_in.Write(vel.x);
		_in.Write(vel.y);
		
		Vector3 loc;
		_in.Write(loc.x);
		_in.Write(loc.y);

		_in.Write(GetRotation());
		wState |= ECRS_Pose;
	}
	else
	{
		_in.Write((bool)false);
	}

	if (mThrustDir != 0.f)
	{
		_in.Write((bool)true);
		_in.Write(mThrustDir > 0.f);
	}
	else
		_in.Write((bool)false);

	if (_dState & ECRS_Color)
	{
		_in.Write((bool)true);
		_in.Write(GetColor());
		wState |= ECRS_Color;
	}
	else
		_in.Write((bool)false);

	if (_dState & ECRS_Health)
	{
		_in.Write((bool)true);
		_in.Write(mHealth, 4);
		wState |= ECRS_Health;
	}
	else
		_in.Write((bool)false);

	return wState;
}