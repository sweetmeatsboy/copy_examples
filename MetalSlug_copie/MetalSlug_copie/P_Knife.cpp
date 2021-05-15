#include "stdafx.h"


const RTTI CP_Knife::m_Rtti("CP_Knife", CObj::m_Rtti);

void CP_Knife::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 20.f, 20.f);

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 40;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_Speed_X = 40.f;
	m_Speed_Y = 40.f;
	m_DeltaCount = 0;		//총알이 이동한 거리를 잴때 사용한다.

	Atk = 2;
}
int CP_Knife::Progress(void)
{
	if (m_fAngle < 45.f && m_fAngle > 0.f || m_fAngle > 315.f && m_fAngle < 360.f)
		m_fAngle = 0.f;
	if (m_fAngle >= 45.f && m_fAngle < 135.f)
		m_fAngle = 90.f;
	if (m_fAngle >= 135.f && m_fAngle < 225.f)
		m_fAngle = 180.f;
	if (m_fAngle >= 225.f && m_fAngle < 315.f)
		m_fAngle = 270.f;

	m_CenterPoint.setX(m_CenterPoint.getX());
	m_CenterPoint.setY(m_CenterPoint.getY());

	m_tInfo.fCX += 10;
	m_tInfo.fCY += 10;

	if (m_tInfo.fCX > 80)
		return 1;
	return 0;
}
void CP_Knife::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f));*/
}
void CP_Knife::Release(void)
{
}

void CP_Knife::CheckCollision(CObj* _Something)
{

}

