#pragma once

class World
{
private:
	World();
	int GetIndexOfGameObject(GameObjectPtr _objPtr);
	vector<GameObjectPtr> mGameObjects;
public:
	static void StaticInit();

	static unique_ptr<World> sInstance;

	void AddGameObject(GameObjectPtr _ptr);
	void RemoveGameObject(GameObjectPtr _ptr);

	void Update();

	const vector<GameObjectPtr>& GetGameObjects() const
	{
		return mGameObjects;
	}
};