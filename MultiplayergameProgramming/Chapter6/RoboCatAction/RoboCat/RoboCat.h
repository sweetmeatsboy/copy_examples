#pragma once
class RoboCat : public GameObject
{
private:
	float mMaxLinearSpeed;
	float mMaxRotationSpeed;

	float mWallRestitution;
	float mCatRestitution;

	uint32_t mPlayerId;

	Vector3 mVelocity;
protected:
	
	float mLastMoveTimestamp;
	float mThrustDir;
	int mHealth;

	bool mIsShooting;
private:
	void AdjustVelocityByThrust(float _delta);
public:
	RoboCat();
public:
	enum ECatReplicationState
	{
		ECRS_Pose = 1 << 0,
		ECRS_Color = 1 << 1,
		ECRS_PlayerId = 1 << 2,
		ECRS_Health = 1 << 3,

		ECRS_AllState = ECRS_Color | ECRS_Health | ECRS_PlayerId | ECRS_Pose,
	};
	static GameObject* StaticCreate()
	{
		return new RoboCat();
	}
	virtual uint32_t GetAllStateMask() const override
	{
		return ECRS_AllState;
	}

	virtual RoboCat* GetAsCat()
	{
		return this;
	}

	virtual void Update() override;

	void ProcessInput(float _delta, const InputState& _state);
	void SimulateMovement(float _delta);

	void ProcessCollisions();
	void ProcessCollisionsWithScreenWalls();

	void SetPlayerId(uint32_t _pid)
	{
		mPlayerId = _pid;
	}
	uint32_t GetPlayerId() const
	{
		return mPlayerId;
	}

	void SetVelocity(const Vector3& velocity)
	{
		mVelocity = velocity;
	}
	const Vector3& GetVelocity() const
	{
		return mVelocity;
	}

	virtual uint32_t Write(OutputMemoryBitStream& _in, uint32_t _dState) const;

};

typedef shared_ptr< RoboCat >	RoboCatPtr;