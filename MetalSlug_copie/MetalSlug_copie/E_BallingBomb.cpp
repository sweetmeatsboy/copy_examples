#include "stdafx.h"


const RTTI CE_BallingBomb::m_Rtti("CE_BallingBomb", CEnemyBullet::m_Rtti);

void CE_BallingBomb::isOutOfFocus()
{
	if (m_tInfo.fX < CObjMgr::GetInst()->GetCam()->m_Left_X - 250)
		isDead = true;
	if (m_tInfo.fX > CObjMgr::GetInst()->GetCam()->m_Right_X + 250)
		isDead = true;
	if (m_tInfo.fY < CObjMgr::GetInst()->GetCam()->m_Left_Y - 250)
		isDead = true;
	if (m_tInfo.fY > CObjMgr::GetInst()->GetCam()->m_Right_Y + 250)
		isDead = true;
}
void CE_BallingBomb::Move()
{
	float _deltaX;
	float _deltaY;
	if (isLanded == false)
	{
		m_Speed_Y += GRAVITY;
		if (PlayerIsMyLeft == false)
		{
			_deltaX = m_CenterPoint.getX() + m_Speed_X;
		}
		else
		{
			_deltaX = m_CenterPoint.getX() - m_Speed_X;
		}
		_deltaY = m_CenterPoint.getY() + (m_Speed_Y);
		SetPos(_deltaX, _deltaY);
	}
	else
	{
		if (PlayerIsMyLeft == false)
		{
			_deltaX = m_CenterPoint.getX() + m_Speed_X;
		}
		else
		{
			_deltaX = m_CenterPoint.getX() - m_Speed_X;
		}
		SetPos(_deltaX, LineOnPosPlayerY);
	}
}
void CE_BallingBomb::SetAngle(float _fAngle)
{
	if (CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->empty() == false)
	{
		if (m_CenterPoint.getX() >
			CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front()->GetCenterPoint().getX())
		{
			PlayerIsMyLeft = true;
		}
	}
}

void CE_BallingBomb::CheckLineCollision()
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
				if (m_CenterPoint.getY() >= LineOnPosPlayerY)
				{
					isLanded = true;
					m_Speed_Y = 0;
				}
			}
			else
			{	//���� ����Ǿ��� ��.
				if (LineOnPosPlayerY + 20 > m_CenterPoint.getY() &&
					LineOnPosPlayerY - 30 < m_CenterPoint.getY())
				{
					isLanded = true;
					m_Speed_Y = 0;
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
void CE_BallingBomb::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().isExactly(CPlayer::m_Rtti))
	{
		isDead = true;
	}
}

void CE_BallingBomb::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 20.f, 20.f);

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_Speed_X = 5.f;
	m_Speed_Y = -10.f;
	m_DeltaCount = 0;		//�Ѿ��� �̵��� �Ÿ��� �궧 ����Ѵ�.

	//���� ���� ���� ����.
	m_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	SelectedLine = NULL;
	m_CurLine = NULL;

	m_Ani = CAniInfoMgr::Getinst()->GetEnemy_Weapon_AniSet(_T("EW_BALLING_BOMB"));
	m_CurFrame = 0;
	m_AniTimer = GetTickCount();
	PlayerIsMyLeft = false;
	isDead = false;

	isLanded = false;
}
int CE_BallingBomb::Progress(void)
{
	if (isDead == false)
	{
		Move();
		isOutOfFocus();
		CheckLineCollision();

		if (GetTickCount() - m_AniTimer > m_Ani->GetFrameDelay(m_CurFrame))
		{
			m_AniTimer = GetTickCount();
			++m_CurFrame;
			if (m_CurFrame >= m_Ani->GetFrameCount())
			{		//��� �� �ݺ��Ǹ鼭 �����Ѵ�.
				m_CurFrame = 0;
			}
		}
		return 0;
	}
	else
	{
		CObj* Explosion = CObjFactory<CExplosion>::CreateObj(m_CenterPoint.getX(), m_CenterPoint.getY());
		((CExplosion*)Explosion)->SetExplosionName("Explosion_BallingBomb");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(Explosion);
		return 1;
	}
}
void CE_BallingBomb::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, m_CurFrame,
		m_tInfo.fX,
		m_tInfo.fY, !PlayerIsMyLeft);

}
void CE_BallingBomb::Release(void)
{
}
