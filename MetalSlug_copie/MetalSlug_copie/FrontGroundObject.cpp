#include "stdafx.h"


const RTTI CFrontGroundObject::m_Rtti("CFrontGroundObject", CObj::m_Rtti);

void CFrontGroundObject::SetObjectAni(const TCHAR* _AniName)
{
	m_Ani = CAniInfoMgr::Getinst()->Get_Nomal_OBJ_1_AniSet(_AniName);
}
void CFrontGroundObject::Initialize(void)
{

	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 600.f, 400.f);

	m_fAngle = 0.f;
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;

	m_AniTimer = GetTickCount();
	m_CurFrame = 0;
}
int CFrontGroundObject::Progress(void)
{
	if (m_Ani != NULL)
	{
		if (GetTickCount() - m_AniTimer > m_Ani->GetFrameDelay(m_CurFrame))
		{
			++m_CurFrame;
			if (m_CurFrame >= m_Ani->GetFrameCount())
			{
				m_CurFrame = 0;
			}
		}
	}
	return 0;
}
void CFrontGroundObject::Render(HDC _hdc)
{
	if (m_Ani != NULL)
	{
		m_Ani->RenderAniSet(_hdc, m_CurFrame,
			m_CenterPoint.getX(), m_CenterPoint.getY(), false);
		/*Rectangle(_hdc,
			int(m_CenterPoint.getX() - 3), int(m_CenterPoint.getY() - 3),
			int(m_CenterPoint.getX() + 3), int(m_CenterPoint.getY() + 3) );*/
	}
}
void CFrontGroundObject::Release(void)
{
}
void CFrontGroundObject::CheckCollision(CObj* _Something)
{
}