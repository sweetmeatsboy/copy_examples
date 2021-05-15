#include "stdafx.h"

const RTTI CPlayer::m_Rtti("CPlayer", CCharacter::m_Rtti);

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

void CPlayer::Initialize(void)
{
	///////////////////////
	//객체 기준 좌표 관련.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 30;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;

	m_PlayerState = PLAYER_IDLE;		//플레이어 등ㅂ장등을 관리하기 위한 용도.
	m_PlayerMode = HUMAN_MODE;		//슬러그 타면 슬러그로, 사람이면 사람으로 바꿔준다.
	m_Type = PLAYER_NONE;

	m_CurPlayer = NULL;		//현재 플레이어 케릭터
	m_SparePlayer = NULL;		//나중에 슬러그를 탔을떄를 위한 용도.

	m_AppearAni = NULL;
	m_CurFrame = 0;
	m_PaternTimer = GetTickCount();

	m_Score = 0;
	m_BombCount = 20;
	m_bulletCount = 0;
}

int CPlayer::Progress(void)
{
	if (m_CurPlayer != NULL)
	{
		if (m_PlayerState == PLAYER_PLAY)
			return ProgressPlay();
		if (m_PlayerState == PLAYER_DEAD)
			return ProgressDead();
		if (m_PlayerState == PLAYER_NONE)
			return ProgressNone();
	}
	else
	{
		if (m_PlayerState == PLAYER_IDLE)
			return ProgressIdle();
		if (m_PlayerState == PLAYER_APPEAR)
			return ProgressAppear();
	}
	return 0;
}
int CPlayer::ProgressIdle()
{	//플레이어가 화면상에 등장하기 전 단계이다. -> 되살아나기 전?
	if (GetAsyncKeyState('1'))	//1P 선택.
	{
		m_PlayerState = PLAYER_APPEAR;
		m_PlayerMode = HUMAN_MODE;
		m_PaternTimer = GetTickCount();

		m_Type = PLAYER_1;	//Eri

		if (m_Type == PLAYER_1)
			m_AppearAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("PLAYER_1_APPEARANCE"));
		if (m_Type == PLAYER_2)
			m_AppearAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("PLAYER_1_APPEARANCE"));
		if (m_Type == PLAYER_3)
			m_AppearAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("PLAYER_1_APPEARANCE"));
		if (m_Type == PLAYER_4)
			m_AppearAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("PLAYER_1_APPEARANCE"));

		return 0;
	}
	if (GetAsyncKeyState('Q'))
		return 1;

	return 0;
}
int CPlayer::ProgressAppear()
{	//플레이어 등장씬이다.
	if (GetTickCount() - m_PaternTimer > m_AppearAni->GetFrameDelay(m_CurFrame))
	{
		m_PaternTimer = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame >= m_AppearAni->GetFrameCount())
		{
			m_PlayerState = PLAYER_PLAY;
			m_CurFrame = 0;

			m_CurPlayer = new CPlayer_1();
			m_CurPlayer->Initialize();
			m_CurPlayer->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
			m_CurPlayer->SetLine(m_Line_List);

			((CPlayer_1*)m_CurPlayer)->SetParent(this);
		}
	}

	return 0;
}
int CPlayer::ProgressPlay()
{	//실제 게임 플레이가 이루어질 progress부분
	if (m_CurPlayer->Progress() == 1)
	{
		m_PlayerState = PLAYER_DEAD;
		m_CurFrame = 0;
		m_AppearAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("PLAYER_1_DEAD_LAND"));
	}
	return 0;

}
int CPlayer::ProgressDead()
{	//죽는 모션등을 재생할 곳.
	if (GetTickCount() - m_PaternTimer > m_AppearAni->GetFrameDelay(m_CurFrame))
	{
		m_PaternTimer = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame >= m_AppearAni->GetFrameCount())
		{	//사망 애니메이션 완료 후.
			m_CurFrame = 0;
			m_PlayerState = PLAYER_IDLE;
		}
	}
	return 0;
}
int CPlayer::ProgressNone()
{	//음.... 예비용 함수.
	return 0;
}

void CPlayer::Render(HDC _hdc)
{
	/*Ellipse(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f) );*/
	if (m_PlayerState == PLAYER_IDLE)
	{
	}
	if (m_PlayerState == PLAYER_APPEAR)
	{
		if (GetTickCount() % 2 == 0)
		{
			m_AppearAni->RenderAniSet(_hdc, m_CurFrame,
				m_CenterPoint.getX(), m_CenterPoint.getY(), false);
		}
	}
	if (m_PlayerState == PLAYER_PLAY)
	{
		if (m_CurPlayer != NULL)
			m_CurPlayer->Render(_hdc);
	}
	if (m_PlayerState == PLAYER_DEAD)
	{
	}
}
void CPlayer::Release(void)
{
	m_Line_List = NULL;
}

void CPlayer::CheckCollision(CObj* _Something)
{	//충돌체에 대한 분류를 해주는 곳.
	RECT tempRect;
	if (IntersectRect(&tempRect, &_Something->GetRect(), &(m_CurPlayer->GetRect())))
	{
		if (m_CurPlayer != NULL)
			m_CurPlayer->CheckCollision(_Something);
	}

}
void CPlayer::InsertPlayer(PLAYER_TYPE _Type)
{
	if (m_CurPlayer != NULL)
	{
		if (m_SparePlayer != NULL)
			delete m_SparePlayer;
	}
}

void CPlayer::LineCollision()
{
	float LineOnPosY_1 = NULL;
	float LineOnPosY_2 = NULL;
	LineOnPosPlayerY = NULL;
	float DistanceA = NULL;
	float DistanceB = NULL;
	SelectedLine = NULL;

	if (NULL != m_Line_List)
	{
		for (m_Line_Pos = m_Line_List->begin();
			m_Line_Pos != m_Line_List->end(); ++m_Line_Pos)
		{
			if (m_CenterPoint.getX() >= (*m_Line_Pos)->m_lPoint.x &&
				m_CenterPoint.getX() < (*m_Line_Pos)->m_rPoint.x)
			{	//플레이어가 특정선위에 있는지를 x좌표 비교로 판단. [1차 비교.]
				if (SelectedLine == NULL)
				{	//조건만족하는 선을 1개 확인할 때.
					SelectedLine = (*m_Line_Pos);
					LineOnPosPlayerY = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					LineOnPosY_1 = LineOnPosPlayerY;
				}
				else
				{	//대가 이상의 선이 조건을 만족할 때. -> 두 선이 플레이어 위 혹은 아래에 위치한 상태.
					//플레이어와의 거리를 비교 후 판단한다.
					LineOnPosY_1 = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					//기존의 선택했던 선상의 Y좌표
					LineOnPosY_2 = (*m_Line_Pos)->m_Slope * (m_CenterPoint.getX() - (*m_Line_Pos)->m_lPoint.x)
						+ (*m_Line_Pos)->m_lPoint.y;
					DistanceA = abs(m_CenterPoint.getY() - LineOnPosY_1);
					DistanceB = abs(m_CenterPoint.getY() - LineOnPosY_2);

					if (DistanceB < DistanceA)
					{	//새로 검색된 선이 더 가까운 경우
						SelectedLine = (*m_Line_Pos);
						LineOnPosPlayerY = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
							+ SelectedLine->m_lPoint.y;
						int temp = (int)LineOnPosPlayerY;
					}
					else
					{
						LineOnPosPlayerY = LineOnPosY_1;
					}
				}
			}
		}
		if (NULL != SelectedLine)
		{	//선 검색이 끝난 후. 플레이어가 선 밑으로 내려가려고 하면 막아야 한다.
			//단 플레이어가 점프를 해서 라인을 뚫고가는것은 막으면 안된다.
			if (m_CurLine == NULL)
				m_CurLine = SelectedLine;
			if (m_CurLine == SelectedLine)
			{
				if (m_Speed_Y >= 0)
				{
					if (m_CenterPoint.getY() >= LineOnPosPlayerY)
					{

						m_CenterPoint.setY(LineOnPosPlayerY);
						m_P_STATE = P_LAND;
					}
				}
				else
					m_P_STATE = P_JUMPING;
			}
			else
			{	//선이 변경되었을 때.
				if (LineOnPosPlayerY > m_CenterPoint.getY())
				{	//위에 있던 선에서 낙하할 때.
					m_P_STATE = P_LANDING;
				}
				else
				{	//아래있던 선에서 점프해서 올라갈 때.
					m_P_STATE = P_JUMPING;
				}
				if (LineOnPosPlayerY + 20 > m_CenterPoint.getY() &&
					LineOnPosPlayerY - 30 < m_CenterPoint.getY())
					m_CurLine = SelectedLine;
			}
		}
	}
	else
	{
		return;
	}
}
