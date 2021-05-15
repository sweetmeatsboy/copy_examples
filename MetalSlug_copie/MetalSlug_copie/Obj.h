#pragma once
#include "Pt.h"
#include "RTTI.h"

class CObj
{
public:
	static const RTTI m_Rtti;
	virtual const RTTI& GetRTTI() { return m_Rtti; }
protected:
	INFO m_tInfo;
	float m_fAngle;
	CPt m_CenterPoint;

	float m_Speed_Y;
	float m_Speed_X;

public:
	virtual void SetAngle(float _fAngle)
	{
		m_fAngle = _fAngle;
	}
	INFO GetInfo(void) {
		return m_tInfo;
	}
public:
	void SetSpeedX(float _val) {
		m_Speed_X = _val;
	}
	float GetSpeedX() const
	{
		return m_Speed_X;
	}
	void SetSpeedY(float _val) {
		m_Speed_Y = _val;
	}
	float GetSpeedY() const
	{
		return m_Speed_Y;
	}

	void SetPos(float _x, float _y);
	RECT GetRect();
	const CPt& GetCenterPoint() const;
public:
	virtual void Initialize() = 0;
	virtual int Progress() = 0;
	virtual void Render(HDC _h) = 0;
	virtual void Release() = 0;
	virtual void CheckCollision(CObj* _other) = 0;
public:
	CObj(void);
	virtual ~CObj(void);
};