#include "RoboCatServerPCH.h"

namespace
{
	const float kRespawnDelay = 3.f;
}

ClientProxy::ClientProxy(const SocketAddress& _addr, const string& _name, int _pid)
	: mSocketAddress(_addr)
	, mName(_name)
	, mPlayerId(_pid)
	, mIsLastMoveTimestampDirty(false)
	, mTimeToRespawn(0.f)
{
	UpdateLastPacketTime();
}



void ClientProxy::UpdateLastPacketTime()
{
	mLastPacketFromClientTime = Timing::sInstance.GetTimef();
}

void ClientProxy::RespawnCatIfNecessary()
{
	if (mTimeToRespawn == 0.f)
		return;

	if (Timing::sInstance.GetFrameStartTime() <= mTimeToRespawn)
		return;
	static_cast<Server*>(Engine::sInstance.get())->SpawnCatForPlayer(mPlayerId);
	mTimeToRespawn = 0.f;
}