#include "stdafx.h"


const RTTI CP_F::m_Rtti("CP_F", CPlayerBullet::m_Rtti);

void CP_F::SetAngle(float _Angle)
{
	m_fAngle = _Angle;
	if ((m_fAngle >= 0.f && m_fAngle <= 45.f) || (m_fAngle >= 325.f && m_fAngle <= 360.f))
	{
		
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_F"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_F"));
		m_Speed_X = 5.f;
		m_Speed_Y = -0.5f;
		m_fAngle = 0.f;
	}
	if (m_fAngle > 45.f && m_fAngle <= 135.f)
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_F_UP"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_F_UP"));
		m_Speed_X = 0.f;
		m_Speed_Y = -0.5f;
		m_fAngle = 90.f;
	}
	if (m_fAngle > 135.f && m_fAngle <= 225.f)
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_F"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_F"));
		isLeft = true;
		m_Speed_X = -5.f;
		m_Speed_Y = -0.5f;
		m_fAngle = 180.f;
	}
	if (m_fAngle > 225.f && m_fAngle <= 325.f)
	{
		m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Player_Weapon_AniSet"), _T("P_W_F_DOWN"));
		//m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_F_DOWN"));
		m_Speed_X = 0.f;
		m_Speed_Y = 0.5f;
		m_fAngle = 270.f;
	}
}
void CP_F::Initialize(void)
{
	m_dwTimer = GetTickCount();
	CurFrame = 0;
	m_Ani = NULL;

	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 100.f;
	m_tInfo.fCY = 100.f;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_Speed_X = 3.f;
	m_Speed_Y = 5.f;
	m_DeltaCount = 0;		//총알이 이동한 거리를 잴때 사용한다.
	isLeft = false;
	isDead = false;

	//현재 라인 정보 설정.
	m_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	SelectedLine = NULL;
	m_CurLine = NULL;
	isDead = false;

	Atk = 0.3f;
}
int CP_F::Progress(void)
{
	if (isDead == false)
	{
		CheckLineCollision();
		if (GetTickCount() - m_dwTimer > m_Ani->GetFrameInfoByIdx(CurFrame)->m_FrameTimer)
		{
			if (m_fAngle == 0.f)
			{
				m_Speed_Y -= 0.1f;
			}
			if (m_fAngle == 90.f)
			{
				m_Speed_Y = -3.f;
			}
			if (m_fAngle == 180.f)
			{
				m_Speed_Y -= 0.1f;
			}
			if (m_fAngle == 270.f)
			{
				m_Speed_Y = 3.1f;
			}
			m_dwTimer = GetTickCount();
			++CurFrame;
			if (CurFrame >= m_Ani->GetFrameCount())
				return 1;
		}
		SetPos(m_CenterPoint.getX() + m_Speed_X, m_CenterPoint.getY() + m_Speed_Y);
		return 0;
	}
	else
		return 1;
}
void CP_F::Render(HDC _hdc)
{
	//Rectangle(_hdc, 
	//	int(m_tInfo.fX - m_tInfo.fCX/2.f),
	//	int(m_tInfo.fY - m_tInfo.fCY/2.f),
	//	int(m_tInfo.fX + m_tInfo.fCX/2.f),
	//	int(m_tInfo.fY + m_tInfo.fCY/2.f) );
	m_Ani->RenderAniSet(_hdc, CurFrame,
		m_tInfo.fX, m_tInfo.fY, isLeft);

}
void CP_F::Release(void)
{
}


void CP_F::CheckLineCollision()
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
				if (m_CenterPoint.getY() >= LineOnPosPlayerY)
				{
					if (m_CurLine->m_Slope <= 0.5f && m_CurLine->m_Slope >= 0.f)
						SetAngle(180);
					if (m_CurLine->m_Slope <= 0.0f && m_CurLine->m_Slope >= -0.5f)
						SetAngle(0);
					SetPos(m_CenterPoint.getX(), LineOnPosPlayerY);
					m_Speed_X = 0;
					m_Speed_Y = 0;
				}
			}
			else
			{	//선이 변경되었을 때.
				if (LineOnPosPlayerY + 20 > m_CenterPoint.getY() &&
					LineOnPosPlayerY - 30 < m_CenterPoint.getY())
				{
					if (m_CurLine->m_Slope <= 0.5f && m_CurLine->m_Slope >= 0.f)
					{
						m_Speed_X = 0;
						m_Speed_Y = 0;
						SetAngle(180);
					}
					if (m_CurLine->m_Slope <= 0.0f && m_CurLine->m_Slope >= -0.5f)
					{
						m_Speed_X = 0;
						m_Speed_Y = 0;
						SetAngle(0);
					}
					SetPos(m_CenterPoint.getX(), LineOnPosPlayerY);

				}
				m_CurLine = SelectedLine;
			}
		}
	}
	else
	{
		return;
	}
}