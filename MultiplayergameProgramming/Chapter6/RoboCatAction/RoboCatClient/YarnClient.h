#pragma once
class YarnClient : public Yarn
{
private:
	SpriteComponentPtr mSpriteComponent;
protected:
	YarnClient();
public:
	static GameObjectPtr StaticCreate()
	{
		return GameObjectPtr(new YarnClient());
	}

	virtual void Read(InputMemoryBitStream& _in) override;
};

