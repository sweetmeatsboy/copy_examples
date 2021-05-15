#pragma once

class CEnemyBullet : public CObj
{
public:
	static const RTTI m_Rtti;
public:
	virtual void Initialize(void) = 0;;
	virtual int Progress(void) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release(void) = 0;
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	CEnemyBullet() {}
	virtual ~CEnemyBullet() {}
};