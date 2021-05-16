#pragma once

class CReactionSoldier : public CSoldier
{
public:
	static const RTTI m_Rtti;
	CAniDCSet* m_ReactionSoldierAni;
private:
	int CurFrame;
	int MaxFrameCount;
	DWORD m_dwAniTimer;
	CSoldier* m_Parent;
public:
	void SetAniName(const TCHAR* _Name);
	void SetParentSoldier(CSoldier* _Parent);
public:
	virtual void LineCollision();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CReactionSoldier() {}
	virtual ~CReactionSoldier() {}
};