#pragma once
class Server : public Engine
{
private:
	Server();
	bool InitNetwrokManager();
	void SetupWorld();

public:
	static bool StaticInit();

	virtual void DoFrame() override;

	virtual int Run();

	void HandleNewClient(ClientProxyPtr _cp);
	void HandleLostClient(ClientProxyPtr _cp);

	RoboCatPtr GetCatForPlayer(int _pid);
	void SpawnCatForPlayer(int _pid);

};

