#pragma once

class CNormalObj : public CObj
{
public:
	static const RTTI m_Rtti;
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:

	virtual void Initialize();
	virtual int Progress();
	virtual void Render(HDC _hdc);
	virtual void Release();
	virtual void CheckCollision(CObj* _other);
};