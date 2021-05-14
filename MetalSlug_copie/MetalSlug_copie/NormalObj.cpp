#include "stdafx.h"


const RTTI CNormalObj::m_Rtti("CNomalObj", CNormalObj::m_Rtti);

void CNormalObj::Initialize(void)
{

}
int CNormalObj::Progress(void)
{
	return 0;
}
void CNormalObj::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
		m_tInfo.fX - m_tInfo.fCX/2.f,
		m_tInfo.fY - m_tInfo.fCY/2.f,
		m_tInfo.fX + m_tInfo.fCX/2.f,
		m_tInfo.fY + m_tInfo.fCY/2.f);*/
}
void CNormalObj::Release(void)
{
}
void CNormalObj::CheckCollision(CObj* _Something)
{

}
