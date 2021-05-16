#include "stdafx.h"

NetworkManager::NetworkManager()
	:mBytesSentThisFrame(0)
	, mDropPacketChance(0.f)
	, mSimulatedLatency(0.f)
{
}

NetworkManager::~NetworkManager()
{
}

bool NetworkManager::Init(uint16_t _port)
{
	mSocket = SocketUtil::CreateUDPSocket(INET);
	SocketAddress ownAddr(INADDR_ANY, _port);
	mSocket->Bind(ownAddr);

	LOG("%d", _port);

	mBytesReceivedPerSecond = WeightedTimedMovingAverage(1.f);
	mBytesSentPerSecond = WeightedTimedMovingAverage(1.f);

	if (mSocket == nullptr)
		return false;

	if (mSocket->SetNonBlockingMode(true) != NO_ERROR)
		return false;
	return true;
}

void NetworkManager::ProcessIncomingPackets()
{
	ReadIncomingPacketsIntoQueue();

	ProcessQueuedPackets();

	UpdateBytesSentLastFrame();
}

void NetworkManager::ReadIncomingPacketsIntoQueue()
{
	char packetMem[1500];
	int packetSize = sizeof(packetMem);

	InputMemoryBitStream inputStream(packetMem, packetSize * 8);
	SocketAddress fromAddr;
	int receivedPacketCount = 0;
	SocketAddress fromAddress;

	int receivedPacketCount = 0;
	int totalReadByteCount = 0;

	while (receivedPacketCount < kMaxPacketsPerFrameCount)
	{
		int readByteCount = mSocket->ReceiveFrom(packetMem, packetSize, fromAddr);
		if (readByteCount == 0)
			break;
		else if (readByteCount == -WSAEWOULDBLOCK)
		{
			HandleConnectinReset(fromAddr);
		}
		else if (readByteCount > 0)
		{
			inputStream.ResetToCapacity(readByteCount); 
			++receivedPacketCount;
			totalReadByteCount += readByteCount;

			if (RoboMath::GetRandomFloat() >= mDropPacketChance)
			{
				float simulatedReceivedTime = Timing::sInstance.GetTimef() + mSimulatedLatency;
				mPacketQeue.emplace(simulatedReceivedTime, inputStream, fromAddr);
			}
			else
			{
				LOG("Packet drop!", 0);
			}
		}
	}

	if (totalReadByteCount > 0)
	{
		mBytesReceivedPerSecond.UpdatePerSecond(static_cast<float>(totalReadByteCount));
	}
}

