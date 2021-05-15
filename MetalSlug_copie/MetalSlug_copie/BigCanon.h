#pragma once



class CAniDCSet;
class CFrameDC;
class CBigCanon : public CObj
{
public:
	static const RTTI m_Rtti;
private:
	float HP;
public:
	enum TurretType
	{		//발사 모션.
		TurretType_1,		//가장 왼쪽을 본다.
		TurretType_2,
		TurretType_3,
		TurretType_4,
		TurretType_5		//가장 오른쪽을 본다.
	};
	enum TurretState
	{
		Turret_IDLE,			//등장, 애니메이션 다 재생하면 Turning으로 자동 전환.
		Turret_TURNING,			//조준
		Turret_FIRE			//발사.-> 발사 애니메이션 다 끝나면 자동으로 Turning으로 전환.
	};
	enum TargetPos
	{	//플레이어 응시 모션.
		Pos_1,
		Pos_2,
		Pos_3,
		Pos_4,
		Pos_5,
		Pos_6,
		Pos_7,
		Pos_8,
		Pos_9,
		Pos_None
	};
	TurretType m_TurretType;
	TurretState m_Turret_State;
	TargetPos m_TargetPosState;

	POINT m_Posin_1;
	int m_PosinLength;
private:
	CAniDCSet* m_TurretAni;
	CFrameDC* m_TurretFrame;
	int CurFrame;
	CObj* m_Target;
	CObj* m_Parent;
	bool isDead;

	int m_DeltaPos_X;
	int m_DeltaPos_Y;

	DWORD m_IdleDelay;	//등장.
	DWORD m_TurningDelay;
	DWORD m_FiringDelay;
	DWORD m_dwFrameTimer;
	DWORD m_dwPaternTimer;
public:
	void CalcDistanceTarget();
	void UpdatePos();
public:
	void SetDeltaPos(int _X, int _Y) { m_DeltaPos_X = _X; m_DeltaPos_Y = _Y; }
public:
	void SetTuerretState(TurretState _State);
public:
	void SetParent(CObj* _Parent);
public:
	void ProgressIdle();
	void ProgressTurning();
	void ProgressFiring();
	void ProgressFire();
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	CBigCanon() {}
	virtual ~CBigCanon() {}
};
