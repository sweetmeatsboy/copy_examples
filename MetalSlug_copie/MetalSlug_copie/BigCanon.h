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
	{		//�߻� ���.
		TurretType_1,		//���� ������ ����.
		TurretType_2,
		TurretType_3,
		TurretType_4,
		TurretType_5		//���� �������� ����.
	};
	enum TurretState
	{
		Turret_IDLE,			//����, �ִϸ��̼� �� ����ϸ� Turning���� �ڵ� ��ȯ.
		Turret_TURNING,			//����
		Turret_FIRE			//�߻�.-> �߻� �ִϸ��̼� �� ������ �ڵ����� Turning���� ��ȯ.
	};
	enum TargetPos
	{	//�÷��̾� ���� ���.
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

	DWORD m_IdleDelay;	//����.
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
