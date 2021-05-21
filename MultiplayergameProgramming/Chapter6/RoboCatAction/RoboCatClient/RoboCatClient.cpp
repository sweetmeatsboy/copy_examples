#include "RoboCatClientPCH.h"

RoboCatClient::RoboCatClient()
	: mTimeLocationBecameOutofSync(0.f),
	mTimeVelocityBecameOutofSync(0.f)
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent
		->SetTexture(TextureManager::sInstance->GetTexture("cat"));
}

void RoboCatClient::HandleDying()
{
	RoboCat::HandleDying();
	if (GetPlayerId() == NetworkManagerClient::sInstance->GetPlayerId())
		HUD::sInstance->SetplayerHealth(0);
}


void RoboCatClient::Update()
{

}

void RoboCatClient::Read(InputMemoryBitStream& _in)
{
	bool stateBit;
	uint32_t readState = 0;

	_in.Read(stateBit);
	if (stateBit)
	{
		uint32_t pId;
		_in.Read(pId);
		SetPlayerId(pId);
		readState |= ECRS_PlayerId;
	}

	float oldRot = GetRotation();
	Vector3 lodLoc = GetLocation();
	Vector3 oldVel = GetVelocity();

	float repRot;
	Vector3 repLoc;
	Vector3 repVel;

	_in.Read(stateBit);
	if (stateBit)
	{
		_in.Read(repVel.x);
		_in.Read(repVel.y);

		SetVelocity(repVel);

		_in.Read(repLoc.x);
		_in.Read(repLoc.y);

		SetLocation(repLoc);

		_in.Read(repRot);
		SetRotation(repRot);

		readState |= ECRS_Pose;
	}

	_in.Read(stateBit);
	if (stateBit)
	{
		_in.Read(stateBit);
		mThrustDir = stateBit ? 1.f : -1.f;
	}
	else
		mThrustDir = 0.f;

	_in.Read(stateBit);
	if(stateBit)
	{
		Vector3 color;
		_in.Read(color);
		SetColor(color);
		readState |= ECRS_Color;
	}

	_in.Read(stateBit);
	if (stateBit)
	{
	
		mHealth = 0;
		_in.Read(mHealth, 4);
		readState |= ECRS_Health;
	}

	if (GetPlayerId() == NetworkManagerClient::sinstance->GetplayerId())
	{
		if ((readState & ECRS_Health) != 0)
		{
			HUD::sInstance->SetPlayerHealth(mHealth);
		}
	}
}