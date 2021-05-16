#include "stdafx.h"

float kDesiredFrameTime = 0.0166f;

Timing Timing::sInstance;

namespace {
	LARGE_INTEGER sStartTime = { 0 };
}

Timing::Timing()
{
	LARGE_INTEGER perfFreq;
	QueryPerformanceFrequency(&perfFreq);
	mPerfCountDuration = 1.0 / perfFreq.QuadPart;

	QueryPerformanceCounter(&sStartTime);

	mLastFrameStartTime = GetTime();
}

void Timing::Update()
{
	double currentTime = GetTime();

	mDeltaTime = (float)(currentTime - mLastFrameStartTime);
	while (mDeltaTime < kDesiredFrameTime)
	{
		currentTime = GetTime();
		mDeltaTime = (float)(currentTime - mLastFrameStartTime);
	}

	mLastFrameStartTime = currentTime;
	mFrameStartTimef = static_cast<float>(mLastFrameStartTime);
}

double Timing::GetTime() const
{
	LARGE_INTEGER curTime, timeSinceStart;
	QueryPerformanceCounter(&curTime);

	timeSinceStart.QuadPart = curTime.QuadPart - sStartTime.QuadPart;

	return timeSinceStart.QuadPart * mPerfCountDuration;
}