#include "stdafx.h"

unique_ptr<World> World::sInstance;

void World::StaticInit()
{
	sInstance.reset(new World());
}

World::World()
{
}

void World::AddGameObject(GameObjectPtr _ptr)
{
	mGameObjects.push_back(_ptr);
	_ptr->SetIndexInWorld(mGameObjects.size() - 1);
}

void World::RemoveGameObject(GameObjectPtr _ptr)
{
	int idx = _ptr->GetIndexInWorld();
	int lastIdx = mGameObjects.size() - 1;
	if (idx != lastIdx)
	{
		mGameObjects[idx] = mGameObjects[lastIdx];
		mGameObjects[idx]->SetIndexInWorld(idx);
	}
	_ptr->SetIndexInWorld(-1);
	mGameObjects.pop_back();
}

void World::Update()
{
	for (int i = 0, c = mGameObjects.size(); i < c; ++i)
	{
		auto ptr = mGameObjects[i];

		if (ptr->DoesWantToDie() == false)
		{
			ptr->Update();
		}

		if (ptr->DoesWantToDie())
		{
			RemoveGameObject(ptr);
			ptr->HandleDying();
			--i;
			--c;
		}
	}
}