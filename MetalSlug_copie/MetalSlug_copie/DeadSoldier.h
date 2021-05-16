#pragma once

class CDeadSoldier : public CSoldier
{
	//제자리에서 노닥거리는 애들.
public:
	static const RTTI m_Rtti;
	CAniDCSet* m_DeadSoldierAni;
private:
	int CurFrame;
	int MaxFrameCount;
	CSoldier* m_Parent;
	DWORD m_dwAniTimer;
public:
	void SetAniName(const TCHAR* _Name);
	void SetParentSoldier(CSoldier* _Parent);
private:
	/*
	28	샷건
	52 일반총
	53 일반총
	54 점프중 죽음?
	55 일반총
	56 일반총
	57 칼빵?
	58 점프중 죽음?
	59 불타죽음 -> 스플레쉬 또는 플레이어 폭탄으로 하자.
	60 점프중 죽음
	62 스플레쉬로 죽음.

	67 엎드려있다가 샷건 또는 슬러그
	68 엎드려 있다가 샷건 또는 슬러그
	69 칼빵
	70 칼빵
	71 엎드려있다가 칼빵
	72 칼빵
	100  불타죽는 놈.
	*/
	void Progress_Dead_();
public:
	virtual void LineCollision();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something) {}
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CDeadSoldier() {}
	virtual ~CDeadSoldier() {}
};