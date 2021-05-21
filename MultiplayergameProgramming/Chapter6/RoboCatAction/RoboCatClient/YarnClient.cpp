#include "RoboCatClientPCH.h"

YarnClient::YarnClient()
{
	mSpriteComponent.reset(new SpriteComponent(this));
	mSpriteComponent->SetTexture(TextureManager::sInstance->GetTexture("yarn"));
}

void YarnClient::Read(InputMemoryBitStream& _in)
{
	bool stateBit;
	_in.Read(stateBit);

	if (stateBit)
	{
		Vector3 loc;
		_in.Read(loc.x);
		_in.Read(loc.y);
		SetLocation(loc);

		Vector3 vel;
		_in.Read(vel.x);
		_in.Read(vel.y);
		Setvelocity(vel);

		float rot;
		_in.Read(rot);
		SetRotation(rot);
	}

	_in.Read(stateBit);
	if (stateBit)
	{
		Vector3 color;
		_in.Read(color);
		SetColor(color);
	}

	_in.Read(stateBit);
	if(stateBit)
		_in.Read(mPlayerId, 8);
}