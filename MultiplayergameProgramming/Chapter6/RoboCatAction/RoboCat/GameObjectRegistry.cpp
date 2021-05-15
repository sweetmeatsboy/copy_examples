#include "stdafx.h"

unique_ptr<GameObjectRegistry> GameObjectRegistry::sInstance;

void GameObjectRegistry::StaticInit()
{
	sInstance.reset(new GameObjectRegistry());
}

GameObjectRegistry::GameObjectRegistry()
{
}

void GameObjectRegistry::RegisterCreationFunction(uint32_t _fNo, GameObjectCreationFunc _func)
{
	mNameToGameObjectCreationFinctionMap[_fNo] = _func;
}

GameObjectPtr GameObjectRegistry::CreateGameObject(uint32_t _fNo)
{
	GameObjectCreationFunc func = mNameToGameObjectCreationFinctionMap[_fNo];
	GameObjectPtr obj = func();

	World::sInstance->AddGameObject(obj);

	return obj;
}