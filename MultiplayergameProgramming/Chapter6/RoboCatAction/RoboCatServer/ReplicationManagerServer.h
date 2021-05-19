#pragma once
class ReplicationManagerServer
{
private:
	unordered_map<int, ReplicationCommand> mNetworkIdToReplicationCommand;
	vector<int> mNetworkIdsToRemove;

private:
	uint32_t WriteCreateAction(OutputMemoryBitStream& _in, int _nid, uint32_t _dState);
	uint32_t WriteUpdateAction(OutputMemoryBitStream& _in, int _nid, uint32_t _dState);
	uint32_t WriteDestroyAction(OutputMemoryBitStream& _in, int _nid, uint32_t _dState);
	
public:
	void ReplicateCreate(int _nid, uint32_t _dState);
	void ReplicateDestroy(int _nid);
	void SetStateDirty(int _nId, uint32_t _dState);
	void RemoveFromRelication(int _nId);
	void Write(OutputMemoryBitStream& _in);
};

