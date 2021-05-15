#pragma once

typedef GameObjectPtr(*GameObjectCreationFunc)();

class GameObjectRegistry
{
public:
	static void StaticInit();
	static unique_ptr<GameObjectRegistry> sInstance;

	void RegisterCreationFunction(uint32_t _fNo, GameObjectCreationFunc _func);

	GameObjectPtr CreateGameObject(uint32_t _fNo);
 private:

	 GameObjectRegistry();

	 unordered_map<int32_t, GameObjectCreationFunc> mNameToGameObjectCreationFinctionMap;
};