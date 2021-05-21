#pragma once
class InputManager
{
private:
	InputState mCurrentState;
	MoveList mMoveList;
	float mNextTimeToSampleInpput;
	const Move* mPendingMove;
private:
	InputManager();
	bool IsTimeToSampleInput();
	const Move& SampleInputAsMove();
public:
	static void StaticInit();
	static unique_ptr<InputManager> sInstance;

	void HandleInput(EInputAction _act, int _kCode);
	const InputState& GetState() const 
	{
		return mCurrentState;
	}

	MoveList& GetMoveList()
	{
		return mMoveList;
	}

	const Move* GetAndClearPendingMove()
	{
		auto ret = mPendingMove;
		mPendingMove = nullptr; 
		return ret;
	}

	void Update();
};

