#include "stdafx.h"


const RTTI CSoldier::m_Rtti("CSoldier", CCharacter::m_Rtti);

void CSoldier::Initialize(void)
{
	SelectedLine = NULL;
	m_Line_List = NULL;
	///////////////////////
	//��ü ���� ��ǥ ����.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 40;
	m_tInfo.fCY = 60;

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
	m_W_Item = NULL;
	m_N_Item = NULL;
	isDead = false;
	isChildDead = false;
}
int CSoldier::Progress(void)
{
	if (isDead == false)
	{
		GetGravity();
		if (m_P_STATE == P_JUMPING && m_Speed_Y >= 0)
			m_P_STATE = P_LANDING;
		LineCollision();
		SetPos(m_CenterPoint.getX() + m_Speed_X, m_CenterPoint.getY() + m_Speed_Y);
		if (m_Patern.empty() == false)
		{
			if (m_Patern.front()->Progress() == 1)
			{
				//���� ������ �� ���� �غ��ϴ� ��.
				//
				if (isChildDead == false)
				{
					delete m_Patern.front();
					m_Patern.front() = NULL;
					m_Patern.pop_front();
					if (m_Patern.empty() == false)
					{	//�ļ� ���� �ʱ�ȭ���� ��.
						m_Patern.front()->SetPos(m_tInfo.fX, m_tInfo.fY);
					}
					else
					{
						if (m_N_Item != NULL)
						{
							m_N_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
							CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_N_Item);
							m_N_Item = NULL;
						}
						if (m_W_Item != NULL)
						{
							m_W_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
							CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_W_Item);
							m_W_Item = NULL;
						}
						return 1;
					}
				}
				else
				{	//�״� �� ������ �� ���־� ��.
					m_tInfo.fCX = 0;
					m_tInfo.fCY = 0;
					CSoldier* DeadMan = m_Patern.back();
					m_Patern.pop_back();
					ClearPaternSoldier();
					m_Patern.push_back(DeadMan);
					isChildDead = false;
				}

			}
			return 0;
		}
		else
		{
			//�������� �ִٸ� ���� �� ��ü �Ҹ�.
			if (m_N_Item != NULL)
			{
				m_N_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
				CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_N_Item);
				m_N_Item = NULL;
			}
			if (m_W_Item != NULL)
			{
				m_W_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
				CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_W_Item);
				m_W_Item = NULL;
			}
			return 1;
		}
	}
	else
	{
		//�Ƹ��� ��� ���� ��
		//�������� �ִٸ� ���� �� ��ü �Ҹ�.
		if (m_N_Item != NULL)
		{
			m_N_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
			CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_N_Item);
			m_N_Item = NULL;
		}
		if (m_W_Item != NULL)
		{
			m_W_Item->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
			CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(m_W_Item);
			m_W_Item = NULL;

		}
		return 1;
	}
}
void CSoldier::Render(HDC _hdc)
{
	//Rectangle(_hdc, 
	//	int(m_CenterPoint.getX() - m_tInfo.fCX/2.f ),
	//	int(m_CenterPoint.getY() - m_tInfo.fCY ),
	//	int(m_CenterPoint.getX() + m_tInfo.fCX/2.f ),
	//	int(m_CenterPoint.getY()) );

	if (m_Patern.empty() == false)
		m_Patern.front()->Render(_hdc);
}
void CSoldier::Release(void)
{
}

void CSoldier::CheckCollision(CObj* _Something)
{
	if (m_Patern.empty() == false)
		m_Patern.front()->CheckCollision(_Something);
}
void CSoldier::ClearPaternSoldier()
{
	list<CSoldier*>::iterator tempIter;
	for (tempIter = m_Patern.begin();
		tempIter != m_Patern.end(); )
	{
		if ((*tempIter))
			delete (*tempIter);
		(*tempIter) = NULL;
		tempIter = m_Patern.erase(tempIter);
	}
}

void CSoldier::InsertWeaonItem(const TCHAR* _Name)	//��ü ���� �� �������� ���ϰ� ��.
{
	//������ ���� �� �ؾߵ� ��.
	if (m_W_Item == NULL)
		m_W_Item = new CW_Item();
	m_W_Item->Initialize();
	m_W_Item->SetWeaponItemName(_Name);
}
void CSoldier::InsertNomalItem(const TCHAR* _Item)	//��ü ���� �� �������� ���ϰ� ��.
{
	//������ ���� �� �ؾߵ� ��.
	if (m_N_Item == NULL)
		m_N_Item = new CN_Item();
	m_N_Item->Initialize();
	m_N_Item->SetNomalItemName(_Item);
}
void CSoldier::SetTarget(CObj* _Target)
{
	m_Target = _Target;
}
void CSoldier::InsertAttackSoldier(const TCHAR* _AtkName)
{
	CAtkSoldier* patern = new CAtkSoldier();
	patern->Initialize();
	patern->SetPos(m_tInfo.fX, m_tInfo.fY);
	patern->SetAngle(m_fAngle);
	patern->SetTarget(m_Target);
	patern->SetLine(m_Line_List);
	patern->SetAniName(_AtkName);
	patern->SetParentSoldier(this);
	m_Patern.push_back(patern);
}
void CSoldier::InsertExtraSoldier(const TCHAR* _ExtraName)
{
	CExtraSoldier* patern = new CExtraSoldier();
	patern->Initialize();
	patern->SetPos(m_tInfo.fX, m_tInfo.fY);
	patern->SetAngle(m_fAngle);
	patern->SetTarget(m_Target);
	patern->SetLine(m_Line_List);
	patern->SetAniName(_ExtraName);
	patern->SetParentSoldier(this);
	m_Patern.push_back(patern);
}
void CSoldier::InsertReactionSoldier(const TCHAR* _ReactionName)
{
	CReactionSoldier* patern = new CReactionSoldier();
	patern->Initialize();
	patern->SetPos(m_tInfo.fX, m_tInfo.fY);
	patern->SetAngle(m_fAngle);
	patern->SetTarget(m_Target);
	patern->SetLine(m_Line_List);
	patern->SetAniName(_ReactionName);
	patern->SetParentSoldier(this);
	m_Patern.push_back(patern);
}
void CSoldier::InsertDeadSoldier(const TCHAR* _Name)
{
	CDeadSoldier* patern = new CDeadSoldier();
	patern->Initialize();
	patern->SetPos(m_tInfo.fX, m_tInfo.fY);
	patern->SetAngle(m_fAngle);
	patern->SetTarget(m_Target);
	patern->SetLine(m_Line_List);
	patern->SetAniName(_Name);
	patern->SetParentSoldier(this);
	m_Patern.push_back(patern);
}

void CSoldier::LineCollision()
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
						m_Speed_X = 0;
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