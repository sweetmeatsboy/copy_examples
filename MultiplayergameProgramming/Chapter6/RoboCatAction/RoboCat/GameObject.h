#pragma once

#define CALSS_IDENTIFICATION(inCode, inClass)	\
enum {											\
	kClassId = inCode							\
};												\
virtual uint32_t GetClassId() const				\
{												\
	return kClassId;							\
}												\
static GameObject* CreateInstance()				\
{												\
return static_cast<GameObject*>(new inClass());	\
}												\

class GameObject
{
private:
	Vector3 mLocation;
	Vector3 mColor;

	float mCollisionRadius;
	float mRotation;
	float mScale;
	int mIndexInWorld;

	bool mDoesWantToDie;
	int mNetworkId;
public:
	CALSS_IDENTIFICATION('GOBJ', GameObject);
	GameObject();
	virtual ~GameObject() {};
	virtual RoboCat* GetAsCat() { return nullptr; }
	virtual uint32_t GetAllStateMask() const { return 0; }

	virtual bool HandleCollisionWithCat(RoboCat* _cat)
	{
		(void)_cat;
		return true;
	}
	virtual void Update();
	virtual void HandleDying()
	{}

	void SetIndexInWorld(int _idx)
	{
		mIndexInWorld = _idx;
	}
	int GetIndexInWorld() const
	{
		return mIndexInWorld;
	}

	void SetRotation(float _r);
	float GetRotation() const
	{
		return mRotation;
	}

	void SetScale(float _scale)
	{
		mScale = _scale;
	}
	float GetScale() const
	{
		return mScale;
	}

	const Vector3& Getlocation() const 
	{
		return mLocation;
	}
	void SetLocation(const Vector3& _vect)
	{
		mLocation = _vect;
	}

	float GetCollisionRadius() const
	{
		return mCollisionRadius;
	}
	void SetCollisionRadius(float _r)
	{
		mCollisionRadius = _r;
	}

	Vector3 GetForwardVector() const;

	void SetColor(const Vector3& _color)
	{
		mColor = _color;
	}
	const Vector3 GetColor() const
	{
		return mColor;
	}

	bool DoesWantToDie() const
	{
		return mDoesWantToDie;
	}
	void SetDoesWantToDie(bool _f)
	{
		mDoesWantToDie = _f;
	}
	int GetNetworkId() const
	{
		return mNetworkId;
	}
	void SetNetworkId(int _nid);

	virtual uint32_t Write(OutputMemoryBitStream& _s, uint32_t _inDirtyState);
	virtual void Read(InputMemoryBitStream& _s);
};

typedef shared_ptr<GameObject> GameObjectPtr;