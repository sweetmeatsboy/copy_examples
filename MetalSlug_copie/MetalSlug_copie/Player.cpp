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
	//��ü ���� ��ǥ ����.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 30;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;

	m_PlayerState = PLAYER_IDLE;		//�÷��̾� ������ �����ϱ� ���� �뵵.
	m_PlayerMode = HUMAN_MODE;		//������ Ÿ�� �����׷�, ����̸� ������� �ٲ��ش�.
	m_Type = PLAYER_NONE;

	m_CurPlayer = NULL;		//���� �÷��̾� �ɸ���
	m_SparePlayer = NULL;		//���߿� �����׸� �������� ���� �뵵.

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
{	//�÷��̾ ȭ��� �����ϱ� �� �ܰ��̴�. -> �ǻ�Ƴ��� ��?
	if (GetAsyncKeyState('1'))	//1P ����.
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
{	//�÷��̾� ������̴�.
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
{	//���� ���� �÷��̰� �̷���� progress�κ�
	if (m_CurPlayer->Progress() == 1)
	{
		m_PlayerState = PLAYER_DEAD;
		m_CurFrame = 0;
		m_AppearAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("PLAYER_1_DEAD_LAND"));
	}
	return 0;

}
int CPlayer::ProgressDead()
{	//�״� ��ǵ��� ����� ��.
	if (GetTickCount() - m_PaternTimer > m_AppearAni->GetFrameDelay(m_CurFrame))
	{
		m_PaternTimer = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame >= m_AppearAni->GetFrameCount())
		{	//��� �ִϸ��̼� �Ϸ� ��.
			m_CurFrame = 0;
			m_PlayerState = PLAYER_IDLE;
		}
	}
	return 0;
}
int CPlayer::ProgressNone()
{	//��.... ����� �Լ�.
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
{	//�浹ü�� ���� �з��� ���ִ� ��.
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
			{	//�÷��̾ Ư�������� �ִ����� x��ǥ �񱳷� �Ǵ�. [1�� ��.]
				if (SelectedLine == NULL)
				{	//���Ǹ����ϴ� ���� 1�� Ȯ���� ��.
					SelectedLine = (*m_Line_Pos);
					LineOnPosPlayerY = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					LineOnPosY_1 = LineOnPosPlayerY;
				}
				else
				{	//�밡 �̻��� ���� ������ ������ ��. -> �� ���� �÷��̾� �� Ȥ�� �Ʒ��� ��ġ�� ����.
					//�÷��̾���� �Ÿ��� �� �� �Ǵ��Ѵ�.
					LineOnPosY_1 = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					//������ �����ߴ� ������ Y��ǥ
					LineOnPosY_2 = (*m_Line_Pos)->m_Slope * (m_CenterPoint.getX() - (*m_Line_Pos)->m_lPoint.x)
						+ (*m_Line_Pos)->m_lPoint.y;
					DistanceA = abs(m_CenterPoint.getY() - LineOnPosY_1);
					DistanceB = abs(m_CenterPoint.getY() - LineOnPosY_2);

					if (DistanceB < DistanceA)
					{	//���� �˻��� ���� �� ����� ���
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
		{	//�� �˻��� ���� ��. �÷��̾ �� ������ ���������� �ϸ� ���ƾ� �Ѵ�.
			//�� �÷��̾ ������ �ؼ� ������ �հ��°��� ������ �ȵȴ�.
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
			{	//���� ����Ǿ��� ��.
				if (LineOnPosPlayerY > m_CenterPoint.getY())
				{	//���� �ִ� ������ ������ ��.
					m_P_STATE = P_LANDING;
				}
				else
				{	//�Ʒ��ִ� ������ �����ؼ� �ö� ��.
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
