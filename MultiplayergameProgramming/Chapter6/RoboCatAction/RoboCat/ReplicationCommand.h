#pragma once
enum ReplicationAction
{
	RA_Create,
	RA_Update,
	RA_Destroy,
	RA_RPC,
	RA_MAX,
};

struct ReplicationCommand
{
private:
	uint32_t mDirtyState;
	ReplicationAction mAction;
public:
	ReplicationCommand() {}
	ReplicationCommand(uint32_t _dState) 
		: mAction(RA_Create)
		, mDirtyState(_dState)
	{
	}

	void HandleCreateAckd()
	{
		if (mAction == RA_Create)
			mAction = RA_Update;
	}

	void AddDirtyState(uint32_t _state)
	{
		mDirtyState |= _state;
	}
	void SetDestroy()
	{
		mAction = RA_Destroy;
	}

	bool HasDirtyState() const 
	{
		return (mAction == RA_Destroy) || (mDirtyState != 0);
	}

	void SetAction(ReplicationAction _act)
	{
		mAction = _act;
	}
	ReplicationAction GetAction() const
	{
		return mAction;
	}
	uint32_t GetDirtyState() const
	{
	}
	inline void ClearDirtyState(uint32_t _state);
};

inline void ReplicationCommand::ClearDirtyState(uint32_t _state)
{
	mDirtyState &= ~_state;
	if (mAction == RA_Destroy)
		mAction = RA_Update;
}