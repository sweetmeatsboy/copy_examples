#include "stdafx.h"

const RTTI CExplosion::m_Rtti("CExplosion", CObj::m_Rtti);

void CExplosion::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 60.f;

	m_fAngle = 0.f;
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;

	m_AniSet = NULL;

	m_AniTimer = GetTickCount();
	CurFrame = 0;
}
int CExplosion::Progress(void)
{
	if (GetTickCount() - m_AniTimer > m_AniSet->GetFrameDelay(CurFrame))
	{
		m_AniTimer = GetTickCount();
		++CurFrame;
		if (CurFrame >= m_AniSet->GetFrameCount())
			return 1;
	}
	return 0;
}
void CExplosion::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f));*/

	m_AniSet->RenderAniSet(_hdc, CurFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
}
void CExplosion::Release(void)
{

}
void CExplosion::SetExplosionName(const char* _Name)
{

	if (strcmp(_Name, "Explosion_Nomal") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Nomal"));
	}
	if (strcmp(_Name, "Explosion_Middle") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Middle"));
	}
	if (strcmp(_Name, "Explosion_Max") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Max"));
	}
	if (strcmp(_Name, "Explosion_Bomb") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Bomb"));
	}
	if (strcmp(_Name, "Explosion_Bomb_Max") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Bomb_Max"));
	}
	if (strcmp(_Name, "Explosion_Mine") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Mine"));
	}
	if (strcmp(_Name, "Explosion_Mine_2") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Mine_2"));
	}
	if (strcmp(_Name, "Explosion_BallingBomb") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_BallingBomb"));
	}
	if (strcmp(_Name, "Explosion_FireBomb") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_FireBomb"));
	}
	if (strcmp(_Name, "Explosion_FireBomb_Max") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_FireBomb_Max"));
	}
	if (strcmp(_Name, "Explosion_FireBomb_Finished") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_FireBomb_Finished"));
	}
	if (strcmp(_Name, "Explosion_Huge") == 0)
	{
		m_AniSet = CAniInfoMgr::Getinst()->Get_ETC_Effect_AniSet(_T("Explosion_Huge"));
	}

	m_AniTimer = GetTickCount();
	CurFrame = 0;
}
