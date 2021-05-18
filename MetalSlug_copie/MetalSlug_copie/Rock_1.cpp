#include "stdafx.h"

const RTTI CRock_1::m_Rtti("CRock_1", CObj::m_Rtti);

void CRock_1::Initialize(void)
{
	m_tInfo = INFO(100, 100, 100, 100);
	m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_NormalObjectAniSet_1"), _T("STAGE_1_ROCK"));
	//m_Ani = CAniInfoMgr::Getinst()->Get_Nomal_OBJ_1_AniSet(_T("STAGE_1_ROCK"));
	m_Line = new CLine();
	CMapMgr::GetInst()->AddLine(m_Line);
}
int CRock_1::Progress(void)
{
	m_Line->m_lPoint.x = LONG(m_tInfo.fX - m_tInfo.fCX / 2.f);
	m_Line->m_rPoint.x = LONG(m_tInfo.fX + m_tInfo.fCX / 2.f);
	m_Line->m_rPoint.y = m_Line->m_lPoint.y = LONG(m_tInfo.fY - 30);
	m_Line->m_Slope = 0;
	return 0;
}
void CRock_1::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, 0, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
}
void CRock_1::Release(void)
{}
void CRock_1::CheckCollision(CObj* _Something)
{}
