#pragma once

class CFrontGroundObject : public CObj
{
private:
	CAniDCSet* m_Ani;
	int m_CurFrame;
	DWORD m_AniTimer;
public:
	static const RTTI m_Rtti;
public:
	void SetObjectAni(const TCHAR* _AniName);
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	CFrontGroundObject() {}
	virtual ~CFrontGroundObject() {}
};