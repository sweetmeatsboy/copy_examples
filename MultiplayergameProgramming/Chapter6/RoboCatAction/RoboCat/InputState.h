#pragma once

class InputState
{
private:
	friend class InputManager;

	float mDesiredRightAmount, mDesiredLeftAmount;
	float mDesiredForwardAmount, mDesiredBackAmount;
	bool mIsShooting;

public:
	InputState()
		: mDesiredBackAmount(0)
		, mDesiredForwardAmount(0)
		, mDesiredLeftAmount(0)
		, mDesiredRightAmount(0)
		, mIsShooting(false)
	{
	}

	float GetDesiredHorizontalDelte() const
	{
		return mDesiredRightAmount - mDesiredLeftAmount;
	}

	float GetDesiredVerticalDelta() const
	{
		return mDesiredForwardAmount - mDesiredBackAmount;
	}

	bool IsShooting() const
	{
		return mIsShooting;
	}

	bool Write(OutputMemoryBitStream& _in) const;
	bool Read(InputMemoryBitStream& _in);
};