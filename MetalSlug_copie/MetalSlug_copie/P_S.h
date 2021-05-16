#pragma once
#include "PlayerBullet.h"

class CAniDCSet;

class CP_S : public CPlayerBullet
{
private:
	CAniDCSet* m_Ani;
	int CurFrame;
	int m_dwTimer;
	bool isLeft;
public:
	static const RTTI m_Rtti;
public:
	virtual void CheckLineCollision();
	virtual void SetAngle(float _Angle);
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
	virtual void CheckCollision(CObj* _Something) {}
public:
	CP_S() {}
	virtual ~CP_S() {}
};


