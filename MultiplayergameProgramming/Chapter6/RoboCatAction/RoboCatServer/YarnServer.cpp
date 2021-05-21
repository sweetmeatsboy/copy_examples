#include "RoboCatServerPCH.h"

YarnServer::YarnServer()
{
	mTimeToDie = Timing::sInstance.GetFrameStartTime() + 1.f;
}

void YarnServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void YarnServer::Update()
{
	Yarn::Update();
	if (Timing::sInstance.GetFrameStartTime() > mTimeToDie)
		SetDoesWantToDie(true);
}


bool YarnServer::HandleCollisionWithCat(RoboCat* _cat)
{
	if (_cat->GetPlayerId() != GetPlayerId())
	{
		SetDoesWantToDie(true);
		static_cast<RoboCatServer*>(_cat)->TakeDamage(GetPlayerId());
	}
	return false;
}