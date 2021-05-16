#include "stdafx.h"

const RTTI CObj::m_Rtti("CObj");

CObj::CObj()
{
}

CObj::~CObj()
{
}

void CObj::SetPos(float _x, float _y)
{
	m_CenterPoint.setX(_x);
	m_CenterPoint.setY(_y);

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
}

RECT CObj::GetRect()
{
	RECT rc = {
		int(m_CenterPoint.getX() - m_tInfo.fCX / 2.f),
		int(m_CenterPoint.getY() - m_tInfo.fCY),
		int(m_CenterPoint.getX() + m_tInfo.fCX / 2.f),
		int(m_CenterPoint.getY() + m_tInfo.fCY)
	};
	return rc;
}

const CPt& CObj::GetCenterPoint()const
{
	return m_CenterPoint;
}
