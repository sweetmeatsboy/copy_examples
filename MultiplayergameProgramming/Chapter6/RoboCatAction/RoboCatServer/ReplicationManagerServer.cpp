#include "RoboCatServerPCH.h"

void ReplicationManagerServer::ReplicateCreate(int _nid, uint32_t _dState)
{
	mNetworkIdToReplicationCommand[_nid] = ReplicationCommand(_dState);
}

void ReplicationManagerServer::ReplicateDestroy(int _nid)
{
	mNetworkIdToReplicationCommand[_nid].SetDestroy();
}

void ReplicationManagerServer::RemoveFromRelication(int _nid)
{
	mNetworkIdToReplicationCommand.erase(_nid);
}

void ReplicationManagerServer::SetStateDirty(int _nid, uint32_t _dState)
{
	mNetworkIdToReplicationCommand[_nid].AddDirtyState(_dState);
}

void ReplicationManagerServer::Write(OutputMemoryBitStream& _in)
{
	for (auto& pair : mNetworkIdToReplicationCommand)
	{
		ReplicationCommand& cmd = pair.second;
		if (cmd.HasDirtyState() == false)
			continue;
		int nid = pair.first;
		_in.Write(nid);

		auto act = cmd.GetAction();
		_in.Write(act, 2);

		uint32_t ret = 0;
		uint32_t dState = cmd.GetDirtyState();

		switch (act)
		{
		case RA_Create:
			ret = WriteCreateAction(_in, nid, dState);
			cmd.SetAction(RA_Update);
			break;
		case RA_Update:
			ret = WriteUpdateAction(_in, nid, dState);
			break;
		case RA_Destroy:
			ret = WriteDestroyAction(_in, nid, dState);
			mNetworkIdsToRemove.emplace_back(nid);
			break;
		}
		cmd.ClearDirtyState(ret);
	}

	if (mNetworkIdsToRemove.empty() != false)
	{
		for (auto id : mNetworkIdsToRemove)
			RemoveFromRelication(id);

		mNetworkIdsToRemove.clear();
	}
}

uint32_t ReplicationManagerServer::WriteCreateAction(OutputMemoryBitStream& _in, uint32_t _dState)
{
}