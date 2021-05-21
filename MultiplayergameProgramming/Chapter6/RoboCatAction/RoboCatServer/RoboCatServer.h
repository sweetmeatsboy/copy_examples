#pragma once
enum ECatControlType
{
	ESCT_Human,
	ESCT_AI,
};

class RoboCatServer : public RoboCat
{
private:
	float mTimeOfNextShot;
	float mTimeBetweenShoot;
	ECatControlType mCatControlType;
private:
	void HandleShooting();
protected:
	RoboCatServer();
public:
	static GameObjectPtr StaticInit() {
		return NetworkManagerServer::sInstance
			->RegisterAndReturn(new RoboCatServer());
	}
	virtual void HandleDying() override;
	virtual void Update() override;

	void SetCatControl(ECatControlType _t)
	{
		mCatControlType = _t;
	}

	void TakeDamage(int _dmg);
};

