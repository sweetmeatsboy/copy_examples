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
void CHelper::InsertWeaonItem(const TCHAR* _Name)	//객체 생성 시 아이템을 지니게 함.
{
	//아이템 생성 시 해야될 것.
	if (m_W_Item == NULL)
		m_W_Item = new CW_Item();
	m_W_Item->Initialize();
	m_W_Item->SetWeaponItemName(_Name);
}
void CHelper::InsertNomalItem(const TCHAR* _Name)	//객체 생성 시 아이템을 지니게 함.
{
	//아이템 생성 시 해야될 것.
	if (m_N_Item == NULL)
		m_N_Item = new CN_Item();
	m_N_Item->Initialize();
	m_N_Item->SetNomalItemName(_Name);
}

void CHelper::Initialize(void)
{
	//객체 라인관련
	SelectedLine = NULL;
	m_Line_List = NULL;
	///////////////////////
	//객체 기준 좌표 관련.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 60;
	m_tInfo.fCY = 100;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 3.f;
	m_Speed_Y = 0.f;

	//애니메이션 관련 내용,.
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
		{	//아이템을 추가한다.
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
	{	//플레이어와 접촉
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
					else
						m_P_STATE = P_LANDING;
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