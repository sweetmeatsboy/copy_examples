#pragma once


typedef unordered_map<int, GameObjectPtr> IntToGameObjectMap;

class NetworkManager
{
private:
	class ReceivedPacket
	{
	private:
		float mReceivedTime;
		InputMemoryBitStream mPacketBuffer;
		SocketAddress mFromAddress;
	public:

		ReceivedPacket(float _recvTime, InputMemoryBitStream& _stream);
		const SocketAddress& GetFromAddress() const
		{
			return mFromAddress;
		}
		float GetReceivedTime() const
		{
			return mReceivedTime;
		}
		InputMemoryBitStream& GetPacketBuffer()
		{
			return mPacketBuffer;
		}
	};

	float mDropPacketChance;
	float mSimulatedLatency;

	int mBytesSentThisFrame;
	queue<ReceivedPacket, list<ReceivedPacket>> mPacketQeue;
	UDPSocketPtr mSocket;

	WeightedTimedMovingAverage mBytesReceivedPerSecond;
	WeightedTimedMovingAverage mBytesSentPerSecond;

	int mBytesSentThisFrame;

	float mDropPacketChance;
	float mSimulatedLatency;

	void	UpdateBytesSentLastFrame();
	void	ReadIncomingPacketsIntoQueue();
	void	ProcessQueuedPackets();

protected:
	IntToGameObjectMap mNetworkIdToGameObjectMap;

public:

	static const uint32_t kHelloCC = 'HELO';
	static const uint32_t kWelcomeCC = 'WLCM';
	static const uint32_t kStateCC = 'STAT';
	static const uint32_t kInputCC = 'INPT';
	static const int kMaxPacketsPerFrameCount = 10;

	NetworkManager();
	virtual ~NetworkManager();

	bool Init(uint16_t _port);
	void ProcessIncomingPackets();

	virtual void ProcessPacket(InputMemoryBitStream& _stream, const SocketAddress& _from) = 0;
	virtual void HandleConnectinReset(const SocketAddress& _from)
	{
		(void)_from;
	}
	void SendPacket(const OutputMemoryBitStream& _stream, const SocketAddress& _from);
	
	const WeightedTimedMovingAverage& GetBytesReceivedPerSecond() const
	{
		return mBytesReceivedPerSecond;
	}

	const WeightedTimedMovingAverage& GetBytesSentPerSecond() const
	{
		return mBytesSentPerSecond;
	}

	void SetDropPacketChance(float _c)
	{
		mDropPacketChance = _c;
	}
	float GetDropPacketChance() const
	{
		return mDropPacketChance;
	}
	void SetSimulatedLatency(float _latency)
	{
		mSimulatedLatency = _latency;
	}
	float GetSimulatedLatency() const
	{
		return mSimulatedLatency;
	}

	inline GameObjectPtr GetGameObject(int _nId) const;
	void AddToNetworkIdToGameObjectMap(GameObjectPtr _ptr);
	void RemoveFromNetworkIdToGameObjectMap(GameObjectPtr _ptr);
};