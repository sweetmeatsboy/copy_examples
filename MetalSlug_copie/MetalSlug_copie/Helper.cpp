#include "stdafx.h"

const RTTI CHelper::m_Rtti("CHelper", CCharacter::m_Rtti);

void CHelper::isOutOfFocus()
{
	if (m_tInfo.fX < CObjMgr::GetInst()->GetCam()->m_Left_X)
		isDead = true;
	if (m_tInfo.fX > CObjMgr::GetInst()->GetCam()->m_Right_X)
		isDead = true;
	if (m_tInfo.fY < CObjMgr::GetInst()->GetCam()->m_Left_Y)
		isDead = true;
	if (m_tInfo.fY > CObjMgr::GetInst()->GetCam()->m_Right_Y)
		isDead = true;
}
void CHelper::InsertWeaonItem(const TCHAR* _Name)	//��ü ���� �� �������� ���ϰ� ��.
{
	//������ ���� �� �ؾߵ� ��.
	if (m_W_Item == NULL)
		m_W_Item = new CW_Item();
	m_W_Item->Initialize();
	m_W_Item->SetWeaponItemName(_Name);
}
void CHelper::InsertNomalItem(const TCHAR* _Name)	//��ü ���� �� �������� ���ϰ� ��.
{
	//������ ���� �� �ؾߵ� ��.
	if (m_N_Item == NULL)
		m_N_Item = new CN_Item();
	m_N_Item->Initialize();
	m_N_Item->SetNomalItemName(_Name);
}

void CHelper::Initialize(void)
{
	//��ü ���ΰ���
	SelectedLine = NULL;
	m_Line_List = NULL;
	///////////////////////
	//��ü ���� ��ǥ ����.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 60;
	m_tInfo.fCY = 100;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_fAngle = 0.f;
	m_Speed_X = 3.f;
	m_Speed_Y = 0.f;

	//�ִϸ��̼� ���� ����,.
	m_Phase = HAING;

	LineOnPosPlayerY = NULL;
	m_P_STATE = P_IDLE;

	m_W_Item = NULL;
	m_N_Item = NULL;
	isDead = false;

	m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_NormalObjectAniSet_1"), _T("PRISONER_HAING"));
	//m_Ani = CAniInfoMgr::Getinst()->Get_Nomal_OBJ_1_AniSet(_T("PRISONER_HAING"));
	GiveFrame = 11;
	m_PaternTimer = GetTickCount();
	m_AniDelay = GetTickCount();
	m_CurFrame = 0;

	m_Dir = false;
}

void CHelper::ProgressHaing()
{
	if (GetTickCount() - m_AniDelay > m_Ani->GetFrameDelay(m_CurFrame))
	{
		m_AniDelay = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame >= m_Ani->GetFrameCount())
			m_CurFrame = 0;
	}
	if (GetTickCount() - m_PaternTimer > 1000)
	{
		m_PaternTimer = GetTickCount();
		m_Speed_X *= -1;
		m_Dir = !m_Dir;
	}
}
void CHelper::ProgressGive()
{
	if (GetTickCount() - m_AniDelay > m_Ani->GetFrameDelay(m_CurFrame))
	{
		m_AniDelay = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame == 11)
		{	//�������� �߰��Ѵ�.
			if (m_W_Item != NULL)
			{
				m_W_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
				CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_W_Item);
				m_W_Item = NULL;
			}
			if (m_N_Item != NULL)
			{
				m_N_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
				CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_N_Item);
				m_N_Item = NULL;
			}
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_NPC_SIR, 0);
		}
		if (m_CurFrame >= m_Ani->GetFrameCount())
		{
			m_Dir = true;
			m_CurFrame = 0;
			m_Phase = RUN;
			m_Speed_X = -4;
			m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_NormalObjectAniSet_1"), _T("PRISONER_RUN"));
			//m_Ani = CAniInfoMgr::Getinst()->Get_Nomal_OBJ_1_AniSet(_T("PRISONER_RUN"));
		}
	}

}
void CHelper::ProgressRun()
{
	if (GetTickCount() - m_AniDelay > m_Ani->GetFrameDelay(m_CurFrame))
	{
		m_AniDelay = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame >= m_Ani->GetFrameCount())
			m_CurFrame = 0;
	}
	isOutOfFocus();
}
int CHelper::Progress(void)
{
	if (isDead == false)
	{
		GetGravity();
		if (m_P_STATE == P_JUMPING && m_Speed_Y >= 0)
			m_P_STATE = P_LANDING;
		LineCollision();
		SetPos(m_CenterPoint.getX() + m_Speed_X, m_CenterPoint.getY() + m_Speed_Y);

		if (m_Phase == HAING)
			ProgressHaing();
		if (m_Phase == GIVE)
			ProgressGive();
		if (m_Phase == RUN)
			ProgressRun();
		return 0;
	}
	else
		return 1;
}
void CHelper::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, m_CurFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), !m_Dir);
}
void CHelper::Release(void)
{
}
void CHelper::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().isExactly(CPlayer::m_Rtti))
	{	//�÷��̾�� ����
		if (m_Phase == HAING)
		{
			m_Speed_X = 0;
			m_Phase = GIVE;
			m_CurFrame = 0;
			m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_NormalObjectAniSet_1"), _T("PRISONER_GIVE"));
			//m_Ani = CAniInfoMgr::Getinst()->Get_Nomal_OBJ_1_AniSet(_T("PRISONER_GIVE"));
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_NPC_THANKYOU, 0);
		}
	}
}

void CHelper::LineCollision()
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
					else
						m_P_STATE = P_LANDING;
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