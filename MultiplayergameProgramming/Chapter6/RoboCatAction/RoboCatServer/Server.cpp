#include "RoboCatServerPCH.h"

bool Server::StaticInit()
{
	sInstance.reset(new Server());
	return true;
}

Server::Server()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction('RCAT', );
	GameObjectRegistry::sInstance->RegisterCreationFunction('MOUS', );
	GameObjectRegistry::sInstance->RegisterCreationFunction('YARN', );

	InitNetwrokManager();

	float latency = 0.0f;

	string latencyString = StringUtils::GetCommandLineArg(2);
	if (latencyString.empty() == false)
		latency = stof(latencyString);

	NetworkManagerServer::sInstance->SetSimulatedLatency(latency);
}


int Server::Run()
{
	SetupWorld();
	return Engine::Run();
}

bool Server::InitNetwrokManager()
{
	string portString = StringUtils::GetCommandLineArg(1);
	uint16_t port = stoi(portString);

	return NetworkManagerServer::StaticInit(port);
}

namespace
{
	void CreateRandomMice(int _mCnt)
	{
		Vector3 mMin(-5.f, -3.f, 0.f);
		Vector3 mMax(5.f, 3.f, 0.f);
		GameObjectPtr go;

		for (int i = 0; i < _mCnt; ++i)
		{
			go = GameObjectRegistry::sInstance->CreateGameObject('MOUS');
			Vector3 mLoc = RoboMath::GetRandomVector(mMin, mMax);
			go->SetLocation(mLoc);
		}
	}
}

void Server::SetupWorld()
{
	CreateRandomMice(10);
	CreateRandomMice(10);
}

void Server::DoFrame()
{
	NetworkManagerServer::sInstance->ProcessIncomingPackets();
	NetworkManagerServer::sInstance->CheckForDisconnects();
	NetworkManagerServer::sInstance->RespawnCats();

	Engine::DoFrame();

	NetworkManagerServer::sInstance->SendOutgoingPackets();
}


void Server::HandleNewClient(ClientProxyPtr _cp)
{
	int pid = _cp->GetPlayerId();
	ScoreBoardManager::sInstance->AddEntry(pid, _cp->GetName());
	SpawnCatForPlayer(pid);
}

void Server::SpawnCatForPlayer(int _pid)
{
	RoboCatPtr cat = std::static_pointer_cast<RoboCat>(GameObjectRegistry
		::sInstance->CreateGameObject('RCAT'));
}