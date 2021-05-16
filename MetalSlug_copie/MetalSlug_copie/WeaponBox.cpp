#include "stdafx.h"
void CWeaponBox::Initialize()
{
	TEST = CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("UIBOX_SET"));
	TEST->GetFrameInfoByIdx(0);
	m_Bullet =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("UIBOX_SET"))->GetFrameInfoByIdx(0)->m_Frame;
	m_Canon =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("UIBOX_SET"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Bomb =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("UIBOX_SET"))->GetFrameInfoByIdx(3)->m_Frame;
	m_OutLineBox =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("UIBOX_SET"))->GetFrameInfoByIdx(4)->m_Frame;

	m_BoxPos_X = 0.f;
	m_BoxPos_Y = 0.f;
	m_Margin_X = 5.f;
	m_Margin_Y = 5.f;

	m_Box_Width = float(m_Bullet->FrameWidth + m_Canon->FrameWidth);
	m_Box_Height = float(m_Bullet->FrameHeight + m_OutLineBox->FrameHeight);

	m_Player = NULL;

	m_BulletCount.Initialize();
	m_BulletCount.SetTextType("BIG_GOLD");
	m_BulletCount.SetTextBoxPos(m_BoxPos_X + m_Margin_X,
		m_BoxPos_Y + m_Bullet->FrameHeight + m_Margin_Y);
	m_BulletCount.SetTextBoxSize(m_Bullet->FrameWidth - 6.f, m_Bullet->FrameHeight - 4.f);

	m_BombCount.Initialize();
	m_BombCount.SetTextType("BIG_GOLD");
	m_BombCount.SetTextBoxPos(m_BoxPos_X + m_Bomb->FrameWidth + m_Margin_X,
		m_BoxPos_Y + m_Bullet->FrameHeight + m_Margin_Y);
	m_BombCount.SetTextBoxSize(m_Bomb->FrameWidth - 6.f, m_Bomb->FrameHeight - 4.f);

	m_MainDC = GetDC(g_hWnd);
	m_TempDC = CreateCompatibleDC(m_MainDC);
	m_hBitmap = (HBITMAP)CreateCompatibleBitmap(m_TempDC, WINCX, WINCY);

	SelectObject(m_TempDC, m_hBitmap);
	ReleaseDC(g_hWnd, m_MainDC);
	DeleteObject(m_hBitmap);

}
void CWeaponBox::SetMarginX(float _MarginX)
{
	m_Margin_X = _MarginX;
}
void CWeaponBox::SetMarginY(float _MarginY)
{
	m_Margin_Y = _MarginY;
}

void CWeaponBox::SetBoxPos(float _x, float _y)
{
	m_BoxPos_X = _x;
	m_BoxPos_Y = _y;

	m_BombCount.SetTextBoxPos(m_BoxPos_X + m_Bomb->FrameWidth + m_Margin_X,
		m_BoxPos_Y + m_Bullet->FrameHeight + m_Margin_Y);
	m_BombCount.SetTextBoxSize(m_Bomb->FrameWidth - 6.f, m_Bomb->FrameHeight - 4.f);

	m_BulletCount.SetTextBoxPos(m_BoxPos_X + m_Margin_X,
		m_BoxPos_Y + m_Bullet->FrameHeight + m_Margin_Y);
	m_BulletCount.SetTextBoxSize(m_Bullet->FrameWidth - 6.f, m_Bullet->FrameHeight - 4.f);


}
void CWeaponBox::SetBoxSize(float _W, float _H)
{
	m_Box_Width = _W;
	m_Box_Height = _H;
}
void CWeaponBox::SetPlayer(CPlayer* _Player)
{
	m_Player = _Player;
}
void CWeaponBox::SetBulletCountSize(float _Width, float _Height)
{
	m_BulletCount.SetTextBoxSize(_Width, _Height);
}
void CWeaponBox::SetBulletCountPos(float _x, float _y)
{
	m_BulletCount.SetTextBoxPos(_x, _y);
}
void CWeaponBox::SetBombCountSize(float _Width, float _Height)
{
	m_BombCount.SetTextBoxSize(_Width, _Height);
}
void CWeaponBox::SetBombCountPos(float _x, float _y)
{
	m_BombCount.SetTextBoxPos(_x, _y);
}



void CWeaponBox::Progress()
{
	if (m_Player != NULL)
	{
		m_BulletCount.SetText(((CPlayer*)CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front())->GetBulletCount());
		m_BombCount.SetText(((CPlayer*)CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front())->GetBombCount());
	}
}
void CWeaponBox::Render(HDC _hdc)
{
	PatBlt(m_TempDC, 0, 0, WINCX, WINCY, RGB(255, 170, 204));
	if (m_Player != NULL)
	{
		StretchBlt(_hdc,
			int(m_BoxPos_X), int(m_BoxPos_Y),
			int(m_Box_Width / 2), int(m_Box_Height),
			CResourceMgr::GetInst()->GetBitDCMap("Atals_UI_Set_1")->GetMemDC(),
			int(m_Bullet->GetFrameRect()->getPoint1().getX()),
			int(m_Bullet->GetFrameRect()->getPoint1().getY()),
			int(m_Bullet->FrameWidth), int(m_Bullet->FrameHeight),
			SRCCOPY);
		StretchBlt(_hdc,
			int(m_BoxPos_X + m_Box_Width / 2), int(m_BoxPos_Y),
			int(m_Box_Width / 2), int(m_Box_Height),
			CResourceMgr::GetInst()->GetBitDCMap("Atals_UI_Set_1")->GetMemDC(),
			int(m_Bomb->GetFrameRect()->getPoint1().getX()),
			int(m_Bomb->GetFrameRect()->getPoint1().getY()),
			int(m_Bomb->FrameWidth), int(m_Bomb->FrameHeight),
			SRCCOPY);
		StretchBlt(_hdc,
			int(m_BoxPos_X), int(m_BoxPos_Y + m_Box_Height / 2),
			int(m_Box_Width), int(m_Box_Height),
			CResourceMgr::GetInst()->GetBitDCMap("Atals_UI_Set_1")->GetMemDC(),
			int(m_OutLineBox->GetFrameRect()->getPoint1().getX()),
			int(m_OutLineBox->GetFrameRect()->getPoint1().getY()),
			int(m_OutLineBox->FrameWidth), int(m_OutLineBox->FrameHeight),
			SRCCOPY);

		//ÅºÃ¢ °¹¼ö ¹× ÆøÅº °¹¼ö ±×¸².




		m_BulletCount.Render(_hdc);
		m_BombCount.Render(_hdc);
	}
	else
	{
		MessageBox(g_hWnd, _T("UI_WeaponBox_Player is NULL"), _T("UI_Error"), MB_OK);
	}
}
void CWeaponBox::Release()
{
	DeleteObject(m_TempDC);
}

