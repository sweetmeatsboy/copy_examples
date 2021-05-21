#include "RoboCatClientPCH.h"

NetworkManagerClient* NetworkManagerClient::sInstance;

namespace
{
	const float kTimeBetweenHellos = 1.f;
	const float kTimeBetweenInputPackets = 0.033f;
}

NetworkManagerClient::NetworkManagerClient()
	:mState(NCS_Uninitialized)
	, mLastRoundTripTime(0.f)
{
}

void NetworkManagerClient::StaticInit(const SocketAddress& _addr, const string& _name)
{
	sInstance = new NetworkManagerClient();
	return sInstance->Init(_addr, _name);
}

void NetworkManagerClient::Init(const SocketAddress& _addr, const string& _name)
{
	NetworkManager::Init(0);

	mServerAddress = _addr;
	mState = NCS_SayingHello;
	mTimeOfLastHello = 0.f;

	mName = _name;

	mAvgRoundTripTime = WeightedTimedMovingAverage(1.f);
}

void NetworkManagerClient::ProcessPacket(InputMemoryBitStream& _in, const SocketAddress& _from)
{
	uint32_t pType;
	_in.Read(pType);
	switch (pType)
	{
	case kWelcomeCC:
		HandleWelcomePacket(_in);
		break;
	case kStateCC:
		HandleStatePacket(_in);
		break;
	}
}

void NetworkManagerClient::SendOutgoingPackets()
{
	switch (mState)
	{
	case NetworkManagerClient::NCS_Uninitialized:
		break;
	case NetworkManagerClient::NCS_SayingHello:
		UpdateSayingHello();
		break;
	case NetworkManagerClient::NCS_Welcomed:
		UpdateSendingInputPacket();
		break;
	}
}

void NetworkManagerClient::UpdateSayingHello()
{
	float time = Timing::sInstance.GetTimef();
	if (time > mTimeOfLastHello + kTimeBetweenHellos)
	{
		SendHelloPacket();
		mTimeOfLastHello = time;
	}
}

void NetworkManagerClient::SendHelloPacket()
{
	OutputMemoryBitStream out;
	out.Write(kHelloCC);
	out.Write(mName);

	SendPacket(out, mServerAddress);
}


void NetworkManagerClient::HandleWelcomePacket(InputMemoryBitStream& _in)
{
	if (mState != NCS_SayingHello)
		return;
	int pid;
	_in.Read(pid);
	mPlayerId = pid;
	mState = NCS_Welcomed;
}

void NetworkManagerClient::HandleStatePacket(InputMemoryBitStream& _in)
{
	if (mState != NCS_Welcomed)
		return;

	ReadLastMoveProcessedOnServerTimestamp(_in);
	HandleScoreBoardState(_in);
	mReplicationManagerClient.Read(_in);
}

void NetworkManagerClient::ReadLastMoveProcessedOnServerTimestamp(InputMemoryBitStream& _in)
{
	bool isDirty;
	_in.Read(isDirty);
	if (isDirty == false)
		return;
	_in.Read(mLastMoveProcessedByServerTimestamp);
	float rtt = Timing::sInstance.GetFrameStartTime() - mLastMoveProcessedByServerTimestamp;
	mAvgRoundTripTime.Update(rtt);

	InputManager::sInstance->GetMoveList()
		.RemovedProcessedMoves(mLastMoveProcessedByServerTimestamp);
}

void NetworkManagerClient::HandleGameObjectState(InputMemoryBitStream& _in)
{
	IntToGameObjectMap map = mNetworkIdToGameObjectMap;

	int sCnt;
	_in.Read(sCnt);
	if (sCnt >0)
	{
		for (int idx = 0; idx < sCnt; idx++)
		{
			int nid;
			uint32_t fCC;
			_in.Read(nid);
			_in.Read(fCC);
			GameObjectPtr go;
			auto igo = mNetworkIdToGameObjectMap.find(nid);
			if (igo == mNetworkIdToGameObjectMap.end())
			{
				go = GameObjectRegistry::sInstance->CreateGameObject(fCC);
				go->SetNetworkId(nid);
				AddToNetworkIdToGameObjectMap(go);
			}
			else
			{
				go = igo->second;
			}
			go->Read(_in);
			map.erase(nid);
		}
	}
	DestroyGameObjectsInMap(map);
}

void NetworkManagerClient::DestroyGameObjectsInMap(const IntToGameObjectMap& _in)
{
	for (auto& pair : _in)
	{
		pair.second->SetDoesWantToDie(true);
		mNetworkIdToGameObjectMap.erase(pair.first);
	}
}

void NetworkManagerClient::UpdateSendingInputPacket()
{
	float time = Timing::sInstance.GetTimef();
	if (time > mTimeOfLastInputPacket + kTimeBetweenInputPackets)
	{
		SendInputPacket();
		mTimeOfLastInputPacket = time;
	}
}

void NetworkManagerClient::SendInputPacket()
{
	MoveList& mList = InputManager::sInstance->GetMoveList();

	if (mList.HashMoves() == false)
		return;

	OutputMemoryBitStream out;
	out.Write(kInputCC);

	int mCnt = mList.GetMoveCount();
	int s = mCnt > 3 ? mCnt - 3 - 1 : 0;
	out.Write(mCnt - s, 2);
	for (int i = s; i < mCnt; ++i)
		mList[i].Write(out);

	SendPacket(out, mServerAddress);
	mList.Clear();
}