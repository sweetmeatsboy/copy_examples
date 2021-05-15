#pragma once

class CBoss : public CObj
{
private:
	enum BOSS_PHASE
	{
		PHASE_1, // 단순 등장 
		PHASE_2, //단순 공격
		PHASE_3, //머리 등장중
		PHASE_4, //머리 등장 후
		PHASE_5, //죽음
		PHASE_6	 //보스객체 소멸.
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
private:	//그림 위치잡기용 점들.
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

	CFrameDC* m_BossHead;	//선미 부분
	CFrameDC* m_BossBody;	//사령탑 부분
	CFrameDC* m_BossTail;	//배기구 부분.

	//부서진 파편들 FrameCD
	CFrameDC* m_Broken_Side_Turret_1;
	CFrameDC* m_Broken_Side_Turret_2;
	CFrameDC* m_Broken_Side_Turret_3;
	CFrameDC* m_Broken_Side_Turret_4;
	CFrameDC* m_Broken_Side_One_Turret_1;
	CFrameDC* m_Broken_Side_One_Turret_2;
	CFrameDC* m_Broken_Side_One_Turret_3;

	CFrameDC* m_Broken_ShipBody;	//선미 부분
	CFrameDC* m_Broken_ShipHead;	//사령탑 부분,

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