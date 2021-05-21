#pragma once

class GameObject;
class NetworkManagerServer : public NetworkManager
{
private:
	typedef unordered_map<int, ClientProxyPtr> IntToClientMap;
	typedef unordered_map<SocketAddress, ClientProxyPtr> AddressToClientMap;

	AddressToClientMap mAddressToClientMap;
	IntToClientMap mPlayerIdToClientMap;

	int mNewPlayerId;
	int mNewNetworkId;

	float mTimeOfLastStatePacket;
	float mTimeBetweenStatePackets;
	float mClientDisconnectTimeout;
private:
	NetworkManagerServer();

	void HandlePacketFromNewClient(InputMemoryBitStream& _in, const SocketAddress& _from);
	void ProcessPacket(ClientProxyPtr _cp, InputMemoryBitStream& _in);

	void SendWelcomePacket(ClientProxyPtr _cp);
	void UpdateAllClients();

	void AddWorldStateToPacket(OutputMemoryBitStream& _in);
	void AddScoreBoardStateToPacket(OutputMemoryBitStream& _in);

	void SendStatePacketToClient(ClientProxyPtr _cp);
	void WriteLAstMoveTimestampDirty(OutputMemoryBitStream& _in, ClientProxyPtr _cp);

	void HandleInputPacket(ClientProxyPtr _cp, InputMemoryBitStream& _in);
	void HandleClientDisconnected(ClientProxyPtr _cp);

	int GetNewNetworkId();
public:
	static NetworkManagerServer* sInstance;

	static bool StaticInit(uint16_t _port);
public:
	virtual void ProcessPacket(InputMemoryBitStream& _in, const SocketAddress& _from) override;
	virtual void HandleConnectionReset(const SocketAddress&_from) override;
public:
	void SendOutgoingPackets();
	void CheckForDisconnects();

	void RegisterGameObject(GameObjectPtr _cp);
	inline GameObjectPtr RegisterAndReturn(GameObject* _pObj);
	void UnregisterGameObject(GameObject* _pObj);
	void SetStateDirty(int _nid, uint32_t _dState);

	void RespawnCats();

	ClientProxyPtr GetClientProxy(int _pid) const;
};

inline GameObjectPtr NetworkManagerServer::RegisterAndReturn(GameObject* _p)
{
	GameObjectPtr ret(_p);
	RegisterGameObject(ret);
	return ret;
}