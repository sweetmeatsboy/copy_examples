#pragma once

class Yarn : public GameObject
{
protected:
	Yarn();
	Vector3 mVelocity;
	float mMuzzleSpeed;
	int mPlayerId;
public:
	CLASS_IDENTIFICATION('YARN', GameObject);
	enum EYarnReplicationState
	{
		EYRS_Pose = 1 << 0,
		EYRS_Color = 1 << 1,
		EYRS_PlayerId = 1 << 2,
		EYRS_AllState = EYRS_Color | EYRS_Color | EYRS_PlayerId | EYRS_Pose,
	};

	static GameObject* StaticCreate() { return new Yarn(); }
public:

	void Setvelocity(const Vector3 _vec)
	{
		mVelocity = _vec;
	}
	const Vector3& GetVelocity() const
	{
		return mVelocity;
	}
	void SetPlayerId(int _id)
	{
		mPlayerId = _id;
	}

	int GetPlayerId() const
	{
		return mPlayerId;
	}

	void InitFromShooter(RoboCat* _cat);

	virtual uint32_t GetAllStateMask() const override
	{
		return EYRS_AllState;
	}

	virtual uint32_t Write(OutputMemoryBitStream& _in, uint32_t _dState)const ;
	virtual void Update() override;
	virtual bool HandleCollisionWithCat(RoboCat* _cat) override;
};

typedef shared_ptr<Yarn> YarnPtr;

