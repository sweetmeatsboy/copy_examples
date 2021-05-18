#include "stdafx.h"


void CNPCBonus::SetIconPos(float _X, float _Y)
{
	m_Icon_Pos_X = _X;
	m_Icon_Pos_Y = _Y;
}
void CNPCBonus::SetIconSize(float _W, float _H)
{
	m_Icon_Size_Width = _W;
	m_Icon_Size_Height = _H;
}
void CNPCBonus::Initialize()
{
	m_Icon = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_UI_Set_1_AniSet"), _T("NPC_COUNT"))
		->GetFrameInfoByIdx(0)->m_Frame;
	
	//m_Icon =
	//	CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NPC_COUNT"))->GetFrameInfoByIdx(0)->m_Frame;

	m_Icon_Pos_X = 0;
	m_Icon_Pos_Y = 0;

	m_Icon_Size_Width = m_Icon->FrameWidth;
	m_Icon_Size_Height = m_Icon->FrameHeight;
}
void CNPCBonus::Render(HDC _hdc)
{
	StretchBlt(_hdc,
		int(m_Icon_Pos_X), int(m_Icon_Pos_Y),
		int(m_Icon_Size_Width), int(m_Icon_Size_Height),
		CResourceMgr::GetInst()->GetBitDCMap("Atals_UI_Set_1")->GetMemDC(),
		int(m_Icon->GetFrameRect()->getPoint1().getX()),
		int(m_Icon->GetFrameRect()->getPoint1().getY()),
		int(m_Icon->FrameWidth), int(m_Icon->FrameHeight),
		SRCCOPY);
}
