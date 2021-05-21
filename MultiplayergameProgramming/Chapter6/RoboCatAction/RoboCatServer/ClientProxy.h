#pragma once
class ClientProxy
{
private:
	ReplicationManagerServer mReplicationManagerServer;
	SocketAddress mSocketAddress;
	string mName;
	int mPlayerId;

	float mLastPacketFromClientTime;
	float mTimeToRespawn;

	MoveList mUnprocessedMoveList;
	bool mIsLastMoveTimestampDirty;
public:
	ClientProxy(const SocketAddress& _addr, const string& _name, int _pId);
	const SocketAddress& GetSocketAddress() const
	{
		return mSocketAddress;
	}
	int GetPlayerId() const
	{
		return mPlayerId;
	}
	const string& GetName() const
	{
		return mName;
	}

	void UpdateLastPacketTime();
	float GetLastPacketFromClientTime() const
	{
		return mLastPacketFromClientTime;
	}

	ReplicationManagerServer& GetReplicationManagerServer()
	{
		return mReplicationManagerServer;
	}

<<<<<<< HEAD
	const MoveList& GetUnprodessedMoveList() const
=======
	const MoveList& GetUnprocessedMoveList() const
>>>>>>> MultiplayergameProgramming
	{
		return mUnprocessedMoveList;
	}

	MoveList& GetUnprocessedMoveList()
	{
		return mUnprocessedMoveList;
	}

	void SetIsLastMoveTimestampDirty(bool _dState)
	{
		mIsLastMoveTimestampDirty = _dState;
	}

	bool IsLastMoveTimestampDirty() const
	{
		return mIsLastMoveTimestampDirty;
	}

	void HandleCatDied();
	void RespawnCatIfNecessary();
};

typedef shared_ptr<ClientProxy> ClientProxyPtr;