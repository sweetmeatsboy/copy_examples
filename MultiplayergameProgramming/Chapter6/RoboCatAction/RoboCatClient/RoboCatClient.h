#pragma once
class RoboCatClient : public RoboCat
{
private:
	float mTimeLocationBecameOutofSync;
	float mTimeVelocityBecameOutofSync;

	SpriteComponentPtr mSpriteComponent;
protected:
	RoboCatClient();

public:
	static GameObjectPtr StaticCreate()
	{
		return GameObjectPtr(new RoboCatClient());
	}
	virtual void Update();
	virtual void HandleDying() override;

	virtual void Read(InputMemoryBitStream& _in) override;
};

