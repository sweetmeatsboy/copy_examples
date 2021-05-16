#include "stdafx.h"


const RTTI CDeadSoldier::m_Rtti("CDeadSoldier", CSoldier::m_Rtti);
void CDeadSoldier::SetAniName(const TCHAR* _Name)
{
	m_DeadSoldierAni = CAniInfoMgr::Getinst()->GetNormal_Soldier_AniSet(_Name);
	CurFrame = 0;
	MaxFrameCount = m_DeadSoldierAni->GetFrameCount();
}
void CDeadSoldier::SetParentSoldier(CSoldier* _Parent)
{
	m_Parent = _Parent;
}
void CDeadSoldier::LineCollision()
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
			if (m_Parent->GetCenterPoint().getX() >= SelectedLine->m_lPoint.x &&
				m_Parent->GetCenterPoint().getX() < (*m_Line_Pos)->m_rPoint.x)
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
					LineOnPosY_1 = SelectedLine->m_Slope * (m_Parent->GetCenterPoint().getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					//기존의 선택했던 선상의 Y좌표
					LineOnPosY_2 = (*m_Line_Pos)->m_Slope * (m_Parent->GetCenterPoint().getX() - (*m_Line_Pos)->m_lPoint.x)
						+ (*m_Line_Pos)->m_lPoint.y;
					DistanceA = abs(m_Parent->GetCenterPoint().getY() - LineOnPosY_1);
					DistanceB = abs(m_Parent->GetCenterPoint().getY() - LineOnPosY_2);

					if (DistanceB < DistanceA)
					{	//새로 검색된 선이 더 가까운 경우
						SelectedLine = (*m_Line_Pos);
						LineOnPosPlayerY = SelectedLine->m_Slope
							* (m_Parent->GetCenterPoint().getX() - SelectedLine->m_lPoint.x)
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
					if (m_Parent->GetCenterPoint().getY() >= LineOnPosPlayerY)
					{
						m_Parent->SetPos(m_Parent->GetCenterPoint().getX(), LineOnPosPlayerY);
						m_P_STATE = P_LAND;
					}
					else
						m_P_STATE = P_LANDING;
				}
				else
					m_P_STATE = P_JUMPING;
			}
			else
			{	//선이 변경되었을 때.
				if (LineOnPosPlayerY > m_Parent->GetCenterPoint().getY())
				{	//위에 있던 선에서 낙하할 때.
					m_P_STATE = P_LANDING;
				}
				else
				{	//아래있던 선에서 점프해서 올라갈 때.
					m_P_STATE = P_JUMPING;
				}
				if (LineOnPosPlayerY + 20 > m_Parent->GetCenterPoint().getY() &&
					LineOnPosPlayerY - 30 < m_Parent->GetCenterPoint().getY())
					m_CurLine = SelectedLine;
			}
		}
	}
	else
	{
		return;
	}
}
void CDeadSoldier::Initialize(void)
{
	SelectedLine = NULL;
	m_Line_List = NULL;
	///////////////////////
	//객체 기준 좌표 관련.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;

	memset(tempStr, 0, sizeof(tempStr));
	//객체 라인관련
	LineOnPosPlayerY = NULL;
	m_P_STATE = P_IDLE;
	//애니메이션 관련 내용,.
	m_dwAniTimer = GetTickCount();
	CurFrame = 0;
	m_Parent = NULL;
}
int CDeadSoldier::Progress(void)
{
	SetPos(m_Parent->GetCenterPoint().getX(), m_Parent->GetCenterPoint().getY() + m_Speed_Y);
	if (GetTickCount() - m_dwAniTimer > m_DeadSoldierAni->GetFrameInfoByIdx(CurFrame)->m_FrameTimer)
	{
		m_dwAniTimer = GetTickCount();
		++CurFrame;
		if (CurFrame >= m_DeadSoldierAni->GetFrameCount())
		{
			CurFrame = 0;
			m_Parent->isChildDead = false;
			return 1;
		}
	}
	return 0;
}
void CDeadSoldier::Render(HDC _hdc)
{
	m_DeadSoldierAni->RenderAniSet(_hdc, CurFrame,
		m_Parent->GetCenterPoint().getX(), m_Parent->GetCenterPoint().getY(), true);
}
void CDeadSoldier::Release(void)
{
}