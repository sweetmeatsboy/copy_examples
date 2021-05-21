#pragma once
class NetworkManagerClient : public NetworkManager
{
	enum NetworkClientState
	{
		NCS_Uninitialized,
		NCS_SayingHello,
		NCS_Welcomed,
	};
private:
	ReplicationManagerClient mReplicationManagerClient;
	SocketAddress mServerAddress;

	NetworkClientState mState;

	float mTimeOfLastHello;
	float mTimeOfLastInputPacket;

	string mName;
	int mPlayerId;

	float mLastMoveProcessedByServerTimestamp;

	WeightedTimedMovingAverage mAvgRoundTripTime;
	float mLastRoundTripTime;
private:
	NetworkManagerClient();
	void Init(const SocketAddress& _addr, const string& _name);
	void UpdateSayingHello();
	void SendHelloPacket();

	void HandleWelcomePacket(InputMemoryBitStream& _in);
	void HandleStatePacket(InputMemoryBitStream& _in);
	void ReadLastMoveProcessedOnServerTimestamp(InputMemoryBitStream& _in);

	void HandleGameObjectState(InputMemoryBitStream& _in);
	void HandleScoreBoardState(InputMemoryBitStream& _in);

	void UpdateSendingInputPacket();
	void SendInputPacket();

	void DestroyGameObjectsInMap(const IntToGameObjectMap& _map);
public:
	static NetworkManagerClient* sInstance;

	static void StaticInit(const SocketAddress& _addr, const string& _name);
	void SendOutgoingPackets();

	virtual void ProcessPacket(InputMemoryBitStream& _in, const SocketAddress& _addr) override;

	const WeightedTimedMovingAverage& GetAvgRoundTripTime() const
	{
		return mAvgRoundTripTime;
	}

	float GetRoundTripTime() const
	{
		return mAvgRoundTripTime.GetValue();
	}
	int GetPlayerId()
	{
		return mPlayerId;
	}
	float GetLastMoveProcessedByServerTimestamp()
	{
		return mLastMoveProcessedByServerTimestamp;
	}
};

