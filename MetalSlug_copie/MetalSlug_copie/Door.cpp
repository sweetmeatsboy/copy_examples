#include "stdafx.h"


const RTTI CDoor::m_Rtti("CDoor", CNormalObj::m_Rtti);
void CDoor::Initialize(void)
{
	m_tInfo = INFO(100, 100, 200, 250);
	m_Ani = CAniInfoMgr::Getinst()->Get_Nomal_OBJ_1_AniSet(_T("STAGE_1_FRONT_DOOR_1"));
	MovingDistance = 0;
	temp = 1.5f;
	isDead = false;
	MovingDistance = 0.f;

	HP = 20.f;
}
int CDoor::Progress(void)
{
	if (isDead == false)
	{
		return 0;
	}
	else
	{
		MovingDistance += temp;
		m_CenterPoint.setY(m_CenterPoint.getY() - temp);
		if (MovingDistance >= 250.f)
			return 1;
		else
			return 0;
	}
}
void CDoor::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, 0, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
}
void CDoor::Release(void)
{
}
void CDoor::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti))
	{
		HP -= ((CPlayerBullet*)_Something)->GetAtk();
		if (HP <= 0)
			isDead = true;
	}
}
