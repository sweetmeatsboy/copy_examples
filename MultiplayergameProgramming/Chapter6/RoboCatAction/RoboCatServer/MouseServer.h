#pragma once
class MouseServer : public Mouse
{
private:
	MouseServer();
public:
	static GameObjectPtr StaticCreate()
	{
		return NetworkManagerServer::sInstance
		->RegisterAndReturn(new MouseServer());
	}
public:
	void HandleDying() override;
	virtual bool HandleCollisionWithCat(RoboCat* _cat) override;
};

