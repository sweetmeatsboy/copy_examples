#include "stdafx.h"

const RTTI CP_S::m_Rtti("CP_S", CPlayerBullet::m_Rtti);

/*
	ATK은 4;
*/

void CP_S::SetAngle(float _Angle)
{
	m_fAngle = _Angle;
	if ((m_fAngle >= 0.f && m_fAngle <= 45.f) || (m_fAngle >= 325.f && m_fAngle <= 360.f))
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_S"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_S"));
		m_fAngle = 0.f;
		m_tInfo.fCX = 200.f;
		m_tInfo.fCY = 100.f;
		m_Speed_X = 6.f;
		m_Speed_Y = 0.f;
	}
	if (m_fAngle > 45.f && m_fAngle <= 135.f)
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_S_UP"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_S_UP"));
		m_fAngle = 90.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 200.f;
		m_Speed_X = 0.f;
		m_Speed_Y = -6.f;
	}
	if (m_fAngle > 135.f && m_fAngle <= 225.f)
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_S"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_S"));
		isLeft = true;
		m_fAngle = 180.f;
		m_tInfo.fCX = 200.f;
		m_tInfo.fCY = 100.f;
		m_Speed_X = -6.f;
		m_Speed_Y = 0.f;
	}
	if (m_fAngle > 225.f && m_fAngle <= 325.f)
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_S_DOWN"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_S_DOWN"));
		m_fAngle = 270.f;
		m_tInfo.fCX = 100.f;
		m_tInfo.fCY = 200.f;
		m_Speed_X = 0.f;
		m_Speed_Y = 6.f;
	}
}
void CP_S::Initialize(void)
{
	m_dwTimer = GetTickCount();
	CurFrame = 0;
	m_Ani = NULL;

	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;
	m_DeltaCount = 0;		//총알이 이동한 거리를 잴때 사용한다.
	isLeft = false;

	Atk = 0.4f;
}
int CP_S::Progress(void)
{
	if (GetTickCount() - m_dwTimer > m_Ani->GetFrameInfoByIdx(CurFrame)->m_FrameTimer)
	{
		if (CurFrame == 6)
		{
			m_tInfo.fCX = 0;
			m_tInfo.fCY = 0;
		}
		m_dwTimer = GetTickCount();
		++CurFrame;
		if (CurFrame >= m_Ani->GetFrameCount())
			return 1;
	}
	SetPos(m_CenterPoint.getX() + m_Speed_X, m_CenterPoint.getY() + m_Speed_Y);
	return 0;
}
void CP_S::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, CurFrame,
		m_tInfo.fX, m_tInfo.fY, isLeft);

}
void CP_S::Release(void)
{
}

void CP_S::CheckLineCollision()
{

}