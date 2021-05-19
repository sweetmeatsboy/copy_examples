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

void NetworkManagerServer::ProcessPacket(shared_ptr<ClientProxy> _cp, InputMemoryBitStream& _in)
{
}