#include "RoboCatServerPCH.h"

RoboCatServer::RoboCatServer()
	: mCatControlType(ESCT_Human)
	, mTimeOfNextShot(0.f)
	, mTimeBetweenShoot(0.2f)
{
}

void RoboCatServer::HandleDying()
{
	NetworkManagerServer::sInstance->UnregisterGameObject(this);
}

void RoboCatServer::Update()
{
	RoboCat::Update();

	Vector3 oldLoc = GetLocation();
	Vector3 oldVel = GetVelocity();
	float oldRot = GetRotation();

	ClientProxyPtr cp = NetworkManagerServer::sInstance
		->GetClientProxy(GetPlayerId());
	if (cp != nullptr)
	{
		MoveList& mList = cp->GetUnprocessedMoveList();
		for (const auto& move : mList)
		{
			const InputState& input = move.GetInputState();
			float delta = move.GetDeltaTime();
			ProcessInput(delta, input);
			SimulateMovement(delta);
		}
		mList.Clear();
	}
	HandleShooting();
	if (RoboMath::Is2DVectorEqual(oldLoc, GetLocation()) == false
		|| RoboMath::Is2DVectorEqual(oldVel, GetVelocity()) == false
		|| (oldRot != GetRotation()))
	{
		NetworkManagerServer::sInstance
			->SetStateDirty(GetNetworkId(), ECRS_Pose);
	}
}

void RoboCatServer::HandleShooting()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (mIsShooting && Timing::sInstance.GetFrameStartTime() > mTimeOfNextShot)
	{
		mTimeOfNextShot = time + mTimeBetweenShoot;

		YarnPtr yarn = std::static_pointer_cast<Yarn, GameObject>(GameObjectRegistry::sInstance->CreateGameObject('YARN'));
		yarn->InitFromShooter(this);
	}
}

void RoboCatServer::TakeDamage(int _pid)
{
	mHealth--;
	if (mHealth <= 0.f)
	{
		ScoreBoardManager::sInstance->incScore(_pid, 1);

		SetDoesWantToDie(true);

		ClientProxyPtr cp = NetworkManagerServer::sInstance
			->GetClientProxy(GetPlayerId());
		if (cp != nullptr)
			cp->HandleCatDied();
	}

	NetworkManagerServer::sInstance
		->SetStateDirty(GetNetworkId(), ECRS_Health);
}

