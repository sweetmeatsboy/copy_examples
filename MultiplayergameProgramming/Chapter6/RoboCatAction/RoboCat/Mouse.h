#pragma once


class Mouse : public GameObject
{
protected:
	Mouse();
public:
	CLASS_IDENTIFICATION('MOUS', GameObject);

	enum EMouseReplicationState
	{
		EMRS_Pose = 1 << 0,
		EMRS_Color = 1 << 1,

		EMRS_AllState = EMRS_Pose | EMRS_Color
	};
	static GameObject* StaticCreate()
	{
		return new Mouse();
	}

	virtual uint32_t GetAllStateMask() const override
	{
		return EMRS_AllState;
	}
	virtual uint32_t Write(OutputMemoryBitStream& _in, uint32_t _dState) const override;
	virtual void Read(InputMemoryBitStream& _in) override;

	virtual bool HandleCollisionWithCat(RoboCat* _cat) override;
};