#include "stdafx.h"


const RTTI CExtraSoldier::m_Rtti("CExtraSoldier", CSoldier::m_Rtti);

float CExtraSoldier::CalcDistance(CObj* _Target)
{
	float distance_x = (_Target->GetInfo().fX - m_Parent->GetInfo().fX)
		* (_Target->GetInfo().fX - m_Parent->GetInfo().fX);
	float distance_y = (_Target->GetInfo().fY - m_Parent->GetInfo().fY)
		* (_Target->GetInfo().fY - m_Parent->GetInfo().fY);

	return sqrt(distance_y + distance_x);
}
void CExtraSoldier::LineCollision()
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
void CExtraSoldier::Initialize(void)
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
	PlayerIsMyLeft = false;
	//
	isDead = false;
	//�ִϸ��̼� ���� ����,.
	m_dwAniTimer = GetTickCount();
	CurFrame = 0;
	memset(TestStr, 0, sizeof(TestStr));

	m_Parent = NULL;

}
int CExtraSoldier::Progress(void)
{
	SetPos(m_Parent->GetCenterPoint().getX(), m_Parent->GetCenterPoint().getY() + m_Speed_Y);

	if (isDead == false)
	{
		if (m_Target != NULL)
		{
			if (GetTickCount() - m_dwAniTimer > m_ExtraSoldierAni->GetFrameInfoByIdx(CurFrame)->m_FrameTimer)
			{
				m_dwAniTimer = GetTickCount();
				++CurFrame;
				if (CurFrame >= MaxFrameCount)
				{
					if (CalcDistance(m_Target) >= 0 && CalcDistance(m_Target) < 250.f)
					{
						return 1;
					}
					else
						CurFrame = 0;
				}
			}
			return 0;
		}
		else
			return 1;
	}
	else
		return 1;
}
void CExtraSoldier::Render(HDC _hdc)
{
	m_ExtraSoldierAni->RenderAniSet(_hdc, CurFrame,
		m_Parent->GetCenterPoint().getX(), m_Parent->GetCenterPoint().getY(),
		PlayerIsMyLeft);
	/*memset(TestStr, 0, sizeof(TestStr));
	sprintf(TestStr, "(%f||%f)", m_CenterPoint.getX(), m_CenterPoint.getY());
	TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY()+10, TestStr, strlen(TestStr));*/
}
void CExtraSoldier::Release(void)
{
}
void CExtraSoldier::CheckCollision(CObj* _Something)
{
	if (isDead == false)
	{
		srand(GetTickCount());

		if (_Something->GetRTTI().isExactly(CP_Knife::m_Rtti) && isDead == false)
		{	//Į����

			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_KNIFE, 0);

			m_Parent->isChildDead = true;
			int randNum = rand() % 4 + 1;
			if (randNum == 1)
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_57"));
			else if (randNum == 2)
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_69"));
			else if (randNum == 3)
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_70"));
			else
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_72"));
			isDead = true;
		}

		if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti) && isDead == false)
		{
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_SHOTGUN, 0);
			m_Parent->isChildDead = true;
			int randNum = rand() % 3 + 1;
			//�켱 �÷��̾� �Ѿ˿� �ǰ�.
			if (_Something->GetRTTI().isExactly(CP_S::m_Rtti))	//����
			{
				if (randNum == 1)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_67"));
				else
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_68"));
				isDead = true;
			}
			if ((_Something->GetRTTI().isExactly(CP_H::m_Rtti) || _Something->GetRTTI().isExactly(CP_NomalBullet::m_Rtti)) && isDead == false)	//�ӽŰ� �Ǵ� ����.
			{
				if (randNum == 1)
				{
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_1, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_60"));
				}
				else if (randNum == 2)
				{
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_2, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_52"));
				}
				else
				{
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_3, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_53"));
				}
				isDead = true;
			}
			if (_Something->GetRTTI().isExactly(CP_F::m_Rtti) && isDead == false)	//�����Ӽ�
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_FIRE, 0);
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_100"));
				isDead = true;
			}
			if (_Something->GetRTTI().isExactly(CP_Bomb_1::m_Rtti) && isDead == false)	//�����Ӽ�
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_FIRE, 0);
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
				isDead = true;
			}
		}

		if (_Something->GetRTTI().DerivesFrom(CExplosion::m_Rtti) && isDead == false)
		{	//����[���÷���]
			//���߿����� �������� -> ��� �ּ�ó��
			//m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
			//isDead = true;
		}
	}
}

void CExtraSoldier::SetAniName(const TCHAR* _Name)
{
	m_ExtraSoldierAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Nomal_Soldier_AniSet"), _Name);
	//m_ExtraSoldierAni = CAniInfoMgr::Getinst()->GetNormal_Soldier_AniSet(_Name);
	CurFrame = 0;
	MaxFrameCount = m_ExtraSoldierAni->GetFrameCount();
}

void CExtraSoldier::SetParentSoldier(CSoldier* _Parent)
{
	m_Parent = _Parent;
}