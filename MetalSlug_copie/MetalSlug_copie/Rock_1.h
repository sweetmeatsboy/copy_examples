#pragma once

class CRock_1 : public CObj
{
public:
	static const RTTI m_Rtti;
private:
	CLine* m_Line;
	CAniDCSet* m_Ani;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
};