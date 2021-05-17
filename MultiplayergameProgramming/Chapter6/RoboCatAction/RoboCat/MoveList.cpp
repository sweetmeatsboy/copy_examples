#include "stdafx.h"
#include "MoveList.h"

const Move& MoveList::AddMove(const InputState& _state, float _timestamp)
{
	float deltaTime = mLastMoveTimestamp >= 0.1f ?
		_timestamp - mLastMoveTimestamp : 0.f;

	mMoves.emplace_back(_state, _timestamp, deltaTime);
	mLastMoveTimestamp = _timestamp;

	return mMoves.back();
}

bool MoveList::AddMove(const Move& _move)
{
	float timeStamp = _move.GetTimestamp();
	float deltaTime = mLastMoveTimestamp >= 0.f ?
		timeStamp - mLastMoveTimestamp : 0.f;
	mLastMoveTimestamp = timeStamp;
	mMoves.emplace_back(_move.GetInputState(), timeStamp, deltaTime);

	return true;
}

void MoveList::RemovedProcessedMoves(float _lastTimestamp)
{
	while (mMoves.empty() == false
		&& mMoves.front().GetTimestamp() <= _lastTimestamp)
	{
		mMoves.pop_front();
	}
}