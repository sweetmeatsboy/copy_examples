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
					LineOnPosY_1 = SelectedLine->m_Slope * (m_Parent->GetCenterPoint().getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					//������ �����ߴ� ������ Y��ǥ
					LineOnPosY_2 = (*m_Line_Pos)->m_Slope * (m_Parent->GetCenterPoint().getX() - (*m_Line_Pos)->m_lPoint.x)
						+ (*m_Line_Pos)->m_lPoint.y;
					DistanceA = abs(m_Parent->GetCenterPoint().getY() - LineOnPosY_1);
					DistanceB = abs(m_Parent->GetCenterPoint().getY() - LineOnPosY_2);

					if (DistanceB < DistanceA)
					{	//���� �˻��� ���� �� ����� ���
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
		{	//�� �˻��� ���� ��. �÷��̾ �� ������ ���������� �ϸ� ���ƾ� �Ѵ�.
			//�� �÷��̾ ������ �ؼ� ������ �հ��°��� ������ �ȵȴ�.
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
			{	//���� ����Ǿ��� ��.
				if (LineOnPosPlayerY > m_Parent->GetCenterPoint().getY())
				{	//���� �ִ� ������ ������ ��.
					m_P_STATE = P_LANDING;
				}
				else
				{	//�Ʒ��ִ� ������ �����ؼ� �ö� ��.
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
	//��ü ���� ��ǥ ����.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_fAngle = 0.f;
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;

	memset(tempStr, 0, sizeof(tempStr));
	//��ü ���ΰ���
	LineOnPosPlayerY = NULL;
	m_P_STATE = P_IDLE;
	//�ִϸ��̼� ���� ����,.
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