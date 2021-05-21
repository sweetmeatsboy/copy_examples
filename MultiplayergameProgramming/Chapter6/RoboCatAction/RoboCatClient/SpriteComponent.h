#pragma once
class SpriteComponent
{
private:
	Vector3 mOrigin;
	TexturePtr mTexture;

	GameObject* mGameObject;
public:
	SpriteComponent(GameObject* _obj);
	~SpriteComponent();

	virtual void Draw(const SDL_Rect& _rect);
	void SetTexture(TexturePtr _t)
	{
		mTexture = _t;
	}

	Vector3 GetOrigin() const
	{
		return mOrigin;
	}
	void SetOrigin(const Vector3& _other)
	{
		mOrigin = _other;
	}
};

typedef shared_ptr<SpriteComponent> SpriteComponentPtr;

