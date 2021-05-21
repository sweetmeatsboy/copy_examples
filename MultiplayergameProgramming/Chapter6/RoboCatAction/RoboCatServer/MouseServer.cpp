#include "RoboCatServerPCH.h"

MouseServer::MouseServer()
{
}

void MouseServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

bool MouseServer::HandleCollisionWithCat(RoboCat* _cat)
{
	SetDoesWantToDie(true);

	ScoreBoardManager::sInstance->incScore(_cat->GetPlayerId(), 1);
	return false;
}