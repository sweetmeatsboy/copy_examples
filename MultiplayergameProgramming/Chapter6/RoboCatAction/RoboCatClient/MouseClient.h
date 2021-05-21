#pragma once
class MouseClient : public Mouse
{
private:
	SpriteComponentPtr mSpriteComponent;
protected:
	MouseClient();
public:
	static GameObjectPtr StaticCreate()
	{
		return GameObjectPtr(new MouseClient());
	}
};

