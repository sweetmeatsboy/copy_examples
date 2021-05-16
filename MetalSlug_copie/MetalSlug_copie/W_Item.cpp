#include "stdafx.h"
const RTTI CW_Item::m_Rtti("CW_Item", CObj::m_Rtti);

const TCHAR* CW_Item::GetWeaponItemName() const
{
	return m_Ani->GetName();
}
void CW_Item::SetWeaponItemName(const TCHAR* _Name)
{
	m_Ani = CAniInfoMgr::Getinst()->Get_ETC_Item_AniSet(_Name);
	m_CurFrame = 0;
	m_AniTimer = GetTickCount();
}

void CW_Item::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 40.f, 40.f);

	m_fAngle = 0.f;
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;

	isDead = false;
}
int CW_Item::Progress(void)
{
	//애니메이션 재생해야됨.
	if (isDead == false)
	{
		if (GetTickCount() - m_AniTimer > m_Ani->GetFrameDelay(m_CurFrame))
		{
			m_AniTimer = GetTickCount();
			++m_CurFrame;
			if (m_CurFrame >= m_Ani->GetFrameCount())
				m_CurFrame = 0;
		}
		return 0;
	}
	else
		return 1;

}
void CW_Item::Render(HDC _hdc)
{
	//Rectangle(_hdc,
	//	int(m_CenterPoint.getX() - m_tInfo.fCX / 2.f),
	//	int(m_CenterPoint.getY() - m_tInfo.fCY ),
	//	int(m_CenterPoint.getX() + m_tInfo.fCX / 2.f),
	//	int(m_CenterPoint.getY()) );

	m_Ani->RenderAniSet(_hdc, m_CurFrame,
		m_CenterPoint.getX(), m_CenterPoint.getY(), false);
}
void CW_Item::Release(void)
{
}

void CW_Item::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().isExactly(CPlayer::m_Rtti) == true)
	{
		if (wcscmp(m_Ani->GetName(), _T("W_ITEM_H")) == 0)
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ITEM_HEAVUMUSINGUN, 0);
		if (wcscmp(m_Ani->GetName(), _T("W_ITEM_F")) == 0)
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ITEM_FRAMESHOT, 0);
		if (wcscmp(m_Ani->GetName(), _T("W_ITEM_S")) == 0)
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ITEM_SHOTGUN, 0);
		if (wcscmp(m_Ani->GetName(), _T("W_ITEM_RELOAD_BOMB")) == 0)
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ITEM_BURNADE, 0);

		isDead = true;
	}
}