#include "stdafx.h"

CUIMgr* CUIMgr::inst = NULL;

void CUIMgr::SetGameState(GAME_STATE _State)
{
	m_Game_State = _State;
}
void CUIMgr::SetMissionEnded(bool _isEnded)
{
	m_MissionEnded = _isEnded;
}
bool CUIMgr::GetMissionEnded()const
{
	return m_MissionEnded;
}
void CUIMgr::SetPlayer(CPlayer* _Player)
{
	m_Player = _Player;
	m_WeaponBox.SetPlayer(_Player);
}
void CUIMgr::SetCam(CCamera* _Cam)
{
	m_Cam = _Cam;

	m_WeaponBox.SetBoxPos(float(m_Cam->m_Left_X + 160.f), float(m_Cam->m_Left_Y + 10));
	m_ScoreText.SetTextBoxPos(float(m_Cam->m_Left_X + 10.f), float(m_Cam->m_Left_Y + 10));
	m_Lifetext.SetTextBoxPos(float(m_Cam->m_Left_X + 10.f), float(m_Cam->m_Left_Y + 80));
	m_TimeText.SetTextBoxPos(float(m_Cam->m_Left_X + 370.f), float(m_Cam->m_Left_Y + 10));
	m_InsertCoin.SetTextBoxPos(float(m_Cam->m_Right_X - 570.f), float(m_Cam->m_Left_Y + 550));
	m_CreditText.SetTextBoxPos(float(m_Cam->m_Right_X - 470.f), float(m_Cam->m_Right_Y - 10));

}

void CUIMgr::Initialize()
{
	m_Score = 0;
	m_PlayTime = 0;
	m_Credit = 0;
	m_LifeCount = 2;
	memset(m_Life, 0, sizeof(m_Life));

	m_Game_State = GAME_IDLE;	//게임 진행중인지 결과창을 보여줘야 하는지를 구분한다.
	m_MissionEnded = false;
	m_Player = NULL;
	m_Cam = NULL;

	m_PlayTimer = GetTickCount();
	m_PlayTime = 60;

	m_WeaponBox.Initialize();
	m_ScoreText.Initialize();
	m_Lifetext.Initialize();
	m_TimeText.Initialize();
	m_CreditText.Initialize();
	m_InsertCoin.Initialize();	//2P위치에 InsertCoin 띄움.

	m_ScoreText.SetTextType("SMALL_SILVER");
	m_Lifetext.SetTextType("SMALL_GOLD");
	m_TimeText.SetTextType("BIG_GOLD");
	m_CreditText.SetTextType("NOMAL_SILVER");
	m_InsertCoin.SetTextType("BIG_SILVER");	//2P위치에 InsertCoin 띄움.

}
void CUIMgr::Progress()
{
	if (m_Game_State == GAME_RESULT)
	{
	}
	else
	{
		if (GetTickCount() - m_PlayTimer >= SECOND * 3)
		{
			m_PlayTimer = GetTickCount();
			--m_PlayTime;
			if (m_PlayTime <= 0)
				m_PlayTime = 0;
		}
		m_WeaponBox.Progress();
		m_ScoreText.SetText(((CPlayer*)CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front())->GetScore());
		sprintf_s(m_Life, "LIFE%d", m_LifeCount);
		m_Lifetext.SetText(m_Life);
		m_TimeText.SetText(m_PlayTime);
		m_CreditText.SetText("CREDIT00");
		m_InsertCoin.SetText("INSERTCOIN");	//2P위치에 InsertCoin 띄움.

		m_WeaponBox.SetBoxSize(190, 50);
		m_WeaponBox.SetBombCountSize(60.f, 30.f);
		m_WeaponBox.SetBulletCountSize(60.f, 30.f);
		m_ScoreText.SetTextBoxSize(140, 15);
		m_Lifetext.SetTextBoxSize(140, 15);
		m_TimeText.SetTextBoxSize(100, 60);	//추후에 십의자리, 일의자리로 나누어서 표기하자.
		m_InsertCoin.SetTextBoxSize(300, 80);
		m_CreditText.SetTextBoxSize(160, 35);

		m_WeaponBox.SetBoxPos(float(m_Cam->m_Left_X + 180.f),
			float(m_Cam->m_Left_Y + 5));

		m_WeaponBox.GetBombText()->
			SetTextBoxSize(80.f, 30.f);
		m_WeaponBox.GetBulletText()->
			SetTextBoxSize(80.f, 30.f);

		m_WeaponBox.SetBombCountPos(float(m_Cam->m_Left_X + 270.f), float(m_Cam->m_Left_Y + 40.f));
		m_WeaponBox.SetBulletCountPos(float(m_Cam->m_Left_X + 190.f), float(m_Cam->m_Left_Y + 40.f));

		m_ScoreText.SetTextBoxPos(float(m_Cam->m_Left_X + 10.f),
			float(m_Cam->m_Left_Y + 10));
		m_Lifetext.SetTextBoxPos(float(m_Cam->m_Left_X + 10.f),
			float(m_Cam->m_Left_Y + 60));
		m_TimeText.SetTextBoxPos(float(m_Cam->m_Left_X + 370.f),
			float(m_Cam->m_Left_Y + 10));
		m_InsertCoin.SetTextBoxPos(float(m_Cam->m_Left_X - 340.f),
			float(m_Cam->m_Left_Y + 10));
		m_CreditText.SetTextBoxPos(float(m_Cam->m_Right_X - m_CreditText.GetTextBoxWidth() - 20),
			float(m_Cam->m_Right_Y - m_CreditText.GetTextBoxHeight()));

	}
}
void CUIMgr::Render(HDC _hdc)
{
	if (m_Game_State == GAME_RESULT)
		RenderResult(_hdc);
	else
		RenderMission(_hdc);
}

void CUIMgr::RenderMission(HDC _hdc)
{
	m_WeaponBox.Render(_hdc);
	m_ScoreText.Render(_hdc);
	m_Lifetext.Render(_hdc);
	m_TimeText.Render(_hdc);
	m_CreditText.Render(_hdc);
	m_InsertCoin.Render(_hdc);	//2P위치에 InsertCoin 띄움.
}
void CUIMgr::RenderResult(HDC _hdc)
{

}
void CUIMgr::Release()
{
}
