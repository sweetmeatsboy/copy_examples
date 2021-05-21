#include "RoboCatClientPCH.h"

unique_ptr<InputManager> InputManager::sInstance;

namespace
{
	float kTimeBetweenInputSamples = 0.03f;
}

void InputManager::StaticInit()
{
	sInstance.reset(new InputManager());
}

namespace
{
	inline void UpdateDesireVariableFromKey(EInputAction _act, bool& _ioVar)
	{
		if (_act == EIA_Pressed)
			_ioVar = true;
		else if (_act == EIA_Released)
			_ioVar = false;
	}

	inline void UpdateDesireFloatFromKey(EInputAction _act, float& _ioVar)
	{
		if (_act == EIA_Pressed)
			_ioVar = 1.f;
		else if (_act == EIA_Released)
			_ioVar = 0.f;
	}
}

void InputManager::HandleInput(EInputAction _act, int _kCode)
{
	switch (_kCode)
	{
	case 'a':
		UpdateDesireFloatFromKey(_act, mCurrentState.mDesiredLeftAmount);
		break;
	case 's':
		UpdateDesireFloatFromKey(_act, mCurrentState.mDesiredRightAmount);
		break;
	case 'w':
		UpdateDesireFloatFromKey(_act, mCurrentState.mDesiredForwardAmount);
		break;
	case 'd':
		UpdateDesireFloatFromKey(_act, mCurrentState.mDesiredBackAmount);
		break;
	case 'k':
		UpdateDesireVariableFromKey(_act, mCurrentState.mIsShooting);
		break;
	case '+':
	case '=':
		{
		float latency = NetworkManagerClient::sInstance
			->GetSimulatedLatency();
		latency += 0.1f;
		if (latency > 0.5f)
			latency = 0.5f;
		NetworkManagerClient::sInstance->SetSimulatedLatency(latency);
		}
		break;
	case '-':
		float latency = NetworkManagerClient::sInstance->GetsimulatedLatency();
		latency -= 0.1f;
		if (latency < 0.0f)
			latency = 0.0f;
		NetworkManagerClient::sInstance->SetsimualtedLatencu(latency);
		break;
	}
}

InputManager::InputManager()
	: mNextTimeToSampleInpput(0.f)
	, mPendingMove(nullptr)
{
}

const Move& InputManager::SampleInputAsMove()
{
	return mMoveList
		.AddMove(GetState(), Timing::sInstance.GetFrameStartTime());
}

bool InputManager::IsTimeToSampleInput()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if (time > mNextTimeToSampleInpput)
	{
		mNextTimeToSampleInpput = mNextTimeToSampleInpput
			+ kTimeBetweenInputSamples;
		return true;
	}
	return false;
}

void InputManager::Update()
{
	if (IsTimeToSampleInput() == false)
		return;
	mPendingMove = &SampleInputAsMove();
}