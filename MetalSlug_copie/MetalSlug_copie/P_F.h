#pragma once
#include "PlayerBullet.h"
class CAniDCSet;


class CP_F : public CPlayerBullet
{
protected:
	virtual void CheckLineCollision();

private:
	CAniDCSet* m_Ani;
	int CurFrame;
	int m_dwTimer;
	bool isLeft;
public:
	static const RTTI m_Rtti;
public:
	virtual void SetAngle(float _Angle);
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
	virtual void CheckCollision(CObj* _Something) {}
public:
	CP_F() {}
	virtual ~CP_F() {}
};