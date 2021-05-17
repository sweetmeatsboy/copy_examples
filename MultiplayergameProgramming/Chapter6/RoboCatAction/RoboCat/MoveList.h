#pragma once
class MoveList
{
private:
	float mLastMoveTimestamp;
	deque<Move> mMoves;
public:
	typedef deque<Move>::const_iterator const_iter;
	typedef deque<Move>::const_reverse_iterator const_rIter;

	MoveList()
		: mLastMoveTimestamp(-1.f)
	{
	}

	const Move& AddMove(const InputState& _state, float _timestamp);
	bool AddMove(const Move& _move);

	void RemovedProcessedMoves(float _lastTimestamp);

	float GetLastMoveTimestamp() const
	{
		return mLastMoveTimestamp;
	}

	const Move& GetLastMove() const
	{
		mMoves.back();
	}

	void Clear() 
	{
		mMoves.clear();
	}
	bool HashMoves() const
	{
		return mMoves.empty == false;
	}
	int GetMoveCount() const
	{
		return mMoves.size();
	}

	const_iter begin() const
	{
		return mMoves.begin();
	}
	const_iter end() const
	{
		return mMoves.end();
	}
	const Move& operator[] (size_t i) const
	{
		return mMoves[i];
	}
};

