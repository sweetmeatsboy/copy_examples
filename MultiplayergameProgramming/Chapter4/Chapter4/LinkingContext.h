#pragma once
class GameObject;

class LinkingContext
{
public:
	LinkingContext()
		: mNextNetworkId(1)
	{
	}

	uint32_t GetNetworkId(GameObject* _obj, bool _shouldCreateNotFound)
	{
		auto it = mGameObjectToNetworkIdMap.find(_obj);
		if (it != mGameObjectToNetworkIdMap.end())
		{
			return it->second;
		}
		else if (_shouldCreateNotFound)
		{
			uint32_t newNetworkId = mNextNetworkId++;
			AddGameObject(_obj, newNetworkId);
			return newNetworkId;
		}
		return 0;
	}

	GameObject* GetGameObject(uint32_t _nId) const
	{
		auto it = mNetworkIdToGameObjectMap.find(_nId);
		if (it != mNetworkIdToGameObjectMap.end())
			return it->second;
		return nullptr;
	}

	void AddGameObject(GameObject* _obj, uint32_t _nId)
	{
		mNetworkIdToGameObjectMap[_nId] = _obj;
		mGameObjectToNetworkIdMap[_obj] = _nId;
	}

	void RemoveGameObject(GameObject* _obj)
	{
		uint32_t networkId = mGameObjectToNetworkIdMap[_obj];
		mGameObjectToNetworkIdMap.erase(_obj);
		mNetworkIdToGameObjectMap.erase(networkId);
	}

private:
	unordered_map<uint32_t, GameObject*> mNetworkIdToGameObjectMap;
	unordered_map<const GameObject*, uint32_t> mGameObjectToNetworkIdMap;

	uint32_t mNextNetworkId;
};
