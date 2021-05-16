#pragma once

class CBoss : public CObj
{
private:
	enum BOSS_PHASE
	{
		PHASE_1, // �ܼ� ���� 
		PHASE_2, //�ܼ� ����
		PHASE_3, //�Ӹ� ������
		PHASE_4, //�Ӹ� ���� ��
		PHASE_5, //����
		PHASE_6	 //������ü �Ҹ�.
	};
private:
	BOSS_PHASE m_BossPhase;
	DWORD m_PhaseTimer;
	DWORD m_Phase1_Delay;
	DWORD m_Phase2_Delay;
	DWORD m_Phase3_Delay;
	DWORD m_Phase4_Delay;
	DWORD m_Phase5_Delay;

	int deltaShipHeadPosX;

	void ProgressPhase1();
	void ProgressPhase2();
	void ProgressPhase3();
	void ProgressPhase4();
	void ProgressPhase5();
public:
	void UpdateBrokenParstPoint();
public:
	static const RTTI m_Rtti;
private:	//�׸� ��ġ���� ����.
	POINT BrokenTurret_1;
	POINT BrokenTurret_2;
	POINT BrokenTurret_3;
	POINT BrokenTurret_4;

	POINT BrokenOneTurret_1;
	POINT BrokenOneTurret_2;
	POINT BrokenOneTurret_3;


	POINT Radar_R_Point;
	POINT Radar_L_Point;
	POINT Wheel_F_Point;
	POINT Wheel_B_Point;

	POINT Ship_Head;
	POINT Ship_Body;
	POINT Ship_Tail;
private:
	DWORD m_RadarTimer_1;
	int m_CurRadarFrame_1;
	DWORD m_RadarTimer_2;
	int m_CurRadarFrame_2;
private:
	DWORD m_FrontWheelTimer;
	int m_CurFrontWheelFrame;
	DWORD m_BackWheelTimer;
	int m_CurBackWheelFrame;
private:
	CObj* m_Target;
	CObj* m_Side_Turret_1;
	CObj* m_Side_Turret_2;
	CObj* m_Side_Turret_3;
	CObj* m_Side_Turret_4;
	CObj* m_Side_One_Turret_1;
	CObj* m_Side_One_Turret_2;
	CObj* m_Side_One_Turret_3;

	CObj* m_BigCanon;
	list<CObj*> m_PartsList;
	list<CObj*>::iterator m_PartsListPos;
private:
	CAniDCSet* m_FrontWheelAni;
	CAniDCSet* m_BackWheelAni;
	CAniDCSet* m_RightRadar;
	CAniDCSet* m_LeftRadar;

	CFrameDC* m_BossHead;	//���� �κ�
	CFrameDC* m_BossBody;	//���ž �κ�
	CFrameDC* m_BossTail;	//��ⱸ �κ�.

	//�μ��� ����� FrameCD
	CFrameDC* m_Broken_Side_Turret_1;
	CFrameDC* m_Broken_Side_Turret_2;
	CFrameDC* m_Broken_Side_Turret_3;
	CFrameDC* m_Broken_Side_Turret_4;
	CFrameDC* m_Broken_Side_One_Turret_1;
	CFrameDC* m_Broken_Side_One_Turret_2;
	CFrameDC* m_Broken_Side_One_Turret_3;

	CFrameDC* m_Broken_ShipBody;	//���� �κ�
	CFrameDC* m_Broken_ShipHead;	//���ž �κ�,

	bool Turret_1_Broken;
	bool Turret_2_Broken;
	bool Turret_3_Broken;
	bool Turret_4_Broken;
	bool OneTurret_1_Broken;
	bool OneTurret_2_Broken;
	bool OneTurret_3_Broken;

private:
	void RenderBody(HDC _hdc);
	void RenderBrokenParts(HDC _hdc);
private:
	void AddBigCanon();
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
private:
	void ExplosionGenerate();
	DWORD m_ExplossionTimer;
	int roopNum;

public:
	CBoss() {}
	virtual ~CBoss() {}
};