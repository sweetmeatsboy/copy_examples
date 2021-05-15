#pragma once
#include "PlayerBullet.h"
class CFrameDC;
class CAniDCSet;


class CP_H : public CPlayerBullet
{
public:
	static const RTTI m_Rtti;
public:
	bool isDead;
	int m_DeltaCoun;
	bool m_isLeft;
	CAniDCSet* m_Ani;
	int FrameNumber;
	HDC m_MemDC;
	CFrameDC* m_BulletFrame;
public:
	void SetIsLeft(bool _isLeft) { m_isLeft = _isLeft; }
public:
	virtual void CheckLineCollision();
	virtual void SetAngle(float _Angle);
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CP_H() {}
	virtual ~CP_H() {}
};