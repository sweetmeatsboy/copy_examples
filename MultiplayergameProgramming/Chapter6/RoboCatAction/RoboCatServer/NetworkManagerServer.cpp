#include "RoboCatServerPCH.h"

NetworkManagerServer* NetworkManagerServer::sInstance;

NetworkManagerServer::NetworkManagerServer()
	: mNewPlayerId(1)
	, mNewNetworkId(1)
	, mTimeBetweenStatePackets(0.033f)
	, mClientDisconnectTimeout(3.f)
{
}

bool NetworkManagerServer::StaticInit(uint16_t _port)
{
	sInstance = new NetworkManagerServer();
	return sInstance->Init(_port);
}

void NetworkManagerServer::HandleConnectionReset(const SocketAddress& _from)
{
	auto it = mAddressToClientMap.find(_from);
	if (it == mAddressToClientMap.end())
		return;
	handleClientDisconnected(it->second);
}

void NetworkManagerServer::ProcessPacket(InputMemoryBitStream& _in, const SocketAddress& _from)
{
	auto it = mAddressToClientMap.find(_from);
	if (it == mAddressToClientMap.end())
		HandlePacketFromNewClient(_in, _from);
	else
		ProcessPacket((*it).second, _in);
}

<<<<<<< HEAD
void NetworkManagerServer::ProcessPacket(shared_ptr<ClientProxy> _cp, InputMemoryBitStream& _in)
{
=======
void NetworkManagerServer::ProcessPacket(ClientProxyPtr _cp, InputMemoryBitStream& _in)
{
	_cp->UpdateLastPacketTime();
	uint32_t pType;
	switch (pType)
	{
	case kHelloCC:
		SendWelcomePacket(_cp);
		break;
	case kInputCC:
		HandleInputPacket(_cp, _in);
		break;
	default:
		LOG("Unknown packet type received from %s", _cp->GetSocketAddress().ToString().c_str());
		break;
	}
}

void NetworkManagerServer::HandlePacketFromNewClient(InputMemoryBitStream& _in, const SocketAddress& _from)
{
	uint32_t pType;
	_in.Read(pType);
	if (pType != kHelloCC)
	{
		return;
	}

	string name;
	_in.Read(name);
	ClientProxyPtr newClientProxy = make_shared<ClientProxy>(_from, name, mNewPlayerId++);
	mAddressToClientMap[_from] = newClientProxy;
	mPlayerIdToClientMap[newClientProxy->GetPlayerId()] = newClientProxy;

	static_cast<Server*>(Engine::sInstance.get())
		->HandleNewClient(newClientProxy);

	SendWelcomePacket(newClientProxy);

	for (const auto& pair : mNetworkIdToGameObjectMap)
	{
		newClientProxy->GetReplicationManagerServer()
			.ReplicateCreate(pair.first, pair.second);
	}
	
}

void NetworkManagerServer::SendWelcomePacket(ClientProxyPtr _cp)
{
	OutputMemoryBitStream wPacket;

	wPacket.Write(kWelcomeCC);
	wPacket.Write(_cp->GetPlayerId());

	SendPacket(wPacket, _cp->GetSocketAddress());
}

void NetworkManagerServer::RespawnCats()
{
	for (auto it = mAddressToClientMap.begin()
		, end = mAddressToClientMap.end(); it != end; it++)
	{
		ClientProxyPtr cp = it->second;
		cp->RespawnCatIfNecessary();
	}
}

void NetworkManagerServer::SendOutgoingPackets()
{
	for (auto it = mAddressToClientMap.begin()
		, end = mAddressToClientMap.end()
		; it != end; it++)
	{
		ClientProxyPtr cp = it->second;
		if (cp->IsLastMoveTimestampDirty())
			SendStatePacketToClient(cp);
	}
}

void NetworkManagerServer::UpdateAllClients()
{
	for (auto it = mAddressToClientMap.begin(), end = mAddressToClientMap.end()
		; it != end; it++)
	{
		SendStatePacketToClient(it->second);
	}
}

void NetworkManagerServer::SendStatePacketToClient(ClientProxyPtr _cp)
{
	OutputMemoryBitStream out;

	out.Write(kStateCC);
	WriteLAstMoveTimestampDirty(out, _cp);
	AddScoreBoardStateToPacket(out);
	_cp->GetReplicationManagerServer().Write(out);
	SendPacket(out, _cp->GetSocketAddress());
}

void NetworkManagerServer::WriteLAstMoveTimestampDirty(OutputMemoryBitStream& _in, ClientProxyPtr _cp)
{
	bool isTimestampDirty = _cp->IsLastMoveTimestampDirty();
	_in.Write(isTimestampDirty);
	if (isTimestampDirty == false)
		return;
	_in.Write(_cp->GetUnprocessedMoveList().GetLastMoveTimestamp());
	_cp->SetIsLastMoveTimestampDirty(false);
}

void NetworkManagerServer::AddWorldStateToPacket(OutputMemoryBitStream& _in)
{
	const auto& objs = World::sInstance->GetGameObjects();

	_in.Write(objs.size());
	for (GameObjectPtr obj : objs)
	{
		_in.Write(obj->GetNetworkId());
		_in.Write(obj->GetClassId());
		obj->Write(_in, 0xffffffff);
	}
}

void NetworkManagerServer::AddScoreBoardStateToPacket(OutputMemoryBitStream& _in)
{
	ScoreBoardManager::sInstance->Write(_in);
}

int NetworkManagerServer::GetNewNetworkId()
{
	int ret = mNewNetworkId++;
	if (mNewNetworkId < ret)
	{
		//오버 플로우.
	}
	return ret;
}

void NetworkManagerServer::HandleInputPacket(ClientProxyPtr _cp, InputMemoryBitStream& _in)
{
	uint32_t mCnt = 0;
	Move m;
	_in.Read(mCnt, 2);
	for (; mCnt > 0; --mCnt)
	{
		if (m.Read(_in) == false)
			continue;
		if (_cp->GetUnprocessedMoveList().AddMove(m) == false)
			continue;
		_cp->SetIsLastMoveTimestampDirty(true);
	}
}

ClientProxyPtr NetworkManagerServer::GetClientProxy(int _pid) const
{
	auto it = mPlayerIdToClientMap.find(_pid);
	if (it == mPlayerIdToClientMap.end())
		return nullptr;
	return it->second;
}

void NetworkManagerServer::CheckForDisconnects()
{
	vector<ClientProxyPtr>clientToDC;

	float minAllowedLastPacketFromClientTime = Timing::sInstance.GetTimef() 
		- mClientDisconnectTimeout;
	for (const auto& pair : mAddressToClientMap)
	{
		if (pair.second->GetLastPacketFromClientTime() < minAllowedLastPacketFromClientTime)
			clientToDC.push_back(pair.second);
	}
}

void NetworkManagerServer::HandleClientDisconnected(ClientProxyPtr _cp)
{
	mPlayerIdToClientMap.erase(_cp->GetPlayerId());
	mAddressToClientMap.erase(_cp->GetSocketAddress());
	static_cast<Server*>(Engine::sInstance.get())->HandleLostClient(_cp);
	if (mAddressToClientMap.empty())
		Engine::sInstance->SetShouldKeppRunning(false);
}

void NetworkManagerServer::RegisterGameObject(GameObjectPtr _op)
{
	int newNid = this->GetNewNetworkId();
	_op->SetNetworkId(newNid);
	mNetworkIdToGameObjectMap[newNid] = _op;

	for (const auto& pair : mAddressToClientMap)
		pair.second->GetReplicationManagerServer().ReplicateCreate(newNid, _op);
}

void NetworkManagerServer::UnregisterGameObject(GameObject* _op)
{
	int nid = _op->GetNetworkId();
	mNetworkIdToGameObjectMap.erase(nid);

	for (const auto& it : mAddressToClientMap)
		it.second->GetReplicationManagerServer().ReplicateDestroy(nid);
}

void NetworkManagerServer::SetStateDirty(int _nid, uint32_t _dState)
{
	for (const auto& it : mAddressToClientMap)
		it.second->GetReplicationManagerServer().SetStateDirty(_nid, _dState);
>>>>>>> MultiplayergameProgramming
}