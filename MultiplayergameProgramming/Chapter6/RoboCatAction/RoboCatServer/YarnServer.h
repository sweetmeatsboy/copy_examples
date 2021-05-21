#pragma once
class YarnServer : public Yarn
{
private:
	float mTimeToDie;
protected:
	YarnServer();
public:
	static GameObjectPtr StaticCreate() {
		return NetworkManagerServer::sInstance
			->RegisterAndReturn(new YarnServer());
	}
	void HandleDying() override;

	virtual bool HandleCollisionWithCat(RoboCat* _cat) override;

	virtual void Update() override;
};

