#include "RoboCatClientPCH.h"

void ReplicationManagerClient::Read(InputMemoryBitStream& _in)
{
	while (_in.GetRemainingBitCount() >= 32)
	{
		int nid;
		_in.Read(nid);

		uint8_t act;
		_in.Read(act, 2);

		switch (act)
		{
		case RA_Create:
			ReadAndDoCreateAction(_in, nid);
			break;
		case RA_Update:
			ReadAndDoUpdateAction(_in, nid);
			break;
		case RA_Destroy:
			ReadAndDoUpdateAction(_in, nid);
			break;
		}
	}
}

void ReplicationManagerClient::ReadAndDoCreateAction(InputMemoryBitStream& _in, int _nid)
{
	uint32_t fourCCName;
	_in.Read(fourCCName);

	GameObjectPtr gObj = NetworkManagerClient::sInstance->GetGameObject(_nid);
	if (gObj == nullptr)
	{
		gObj = GameObjectRegistry::sInstance->CreateGameObject(fourCCName);
		gObj->SetNetworkId(_nid);
		NetworkManagerClient::sInstance->AddToNetworkIdToGameObjectMap(gObj);

		assert(gameObject->GetClassId() == fourCCName);
	}

	gObj->Read(_in);

}

void ReplicationManagerClient::ReadAndDoUpdateAction(InputMemoryBitStream& _in, int _nid)
{
	GameObjectPtr gObj = NetworkManagerClient::sInstance->GetGameObject(_nid);

	gObj->Read(_in);
}

void ReplicationManagerClient::ReadAndDoDestroyAction(InputMemoryBitStream& _in, int _nid)
{
	GameObjectPtr gObj = NetworkManagerClient::sInstance->GetGameObject(_nid);
	if (gObj == nullptr)
		return;
	gObj->SetDoesWantToDie(true);
	NetworkManagerClient::sinstance->RemoveFromNetworkIdToGameObjectMap(gObj);
}