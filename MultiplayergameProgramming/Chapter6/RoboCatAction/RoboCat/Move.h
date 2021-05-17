#pragma once

class Move
{
private:
	InputState mInputState;
	float mTimestamp;
	float mDeltaTime;

public:
	Move() {}
	Move(const InputState& _state, float _timeStamp, float _deltaTime)
		:mInputState(_state), mTimestamp(_timeStamp), mDeltaTime(_deltaTime)
	{
	}

	const InputState& GetInputState() const
	{
		return mInputState;
	}
	float GetTimestamp() const
	{
		return mTimestamp;
	}
	float GetDeltaTime() const
	{
		return mDeltaTime;
	}

	bool Write(OutputMemoryBitStream& _in) const;
	bool Read(InputMemoryBitStream& _in);
};
