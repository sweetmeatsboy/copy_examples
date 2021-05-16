#pragma once

class CExtraSoldier : public CSoldier
{
	//제자리에서 노닥거리는 애들.
public:
	static const RTTI m_Rtti;
	CAniDCSet* m_ExtraSoldierAni;
private:

	float CalcDistance(CObj* _Target);
	int CurFrame;
	int MaxFrameCount;
	CSoldier* m_Parent;
	DWORD m_dwAniTimer;
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
	CExtraSoldier() {}
	virtual ~CExtraSoldier() {}
};