#include "stdafx.h"

const RTTI CBossBigBullet::m_Rtti("CBossBigBullet", CObj::m_Rtti);

void CBossBigBullet::isOutOfFocus()
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
void CBossBigBullet::Move()
{
	float _deltaX = m_CenterPoint.getX() + m_Speed_X;
	float _deltaY = m_CenterPoint.getY() + m_Speed_Y;

	SetPos(_deltaX, _deltaY);
}
void CBossBigBullet::SetAngle(float _fAngle)
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

void CBossBigBullet::CheckLineCollision()
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
					CObj* Explosion = CObjFactory<CExplosion>::CreateObj(m_CenterPoint.getX(), m_CenterPoint.getY());
					((CExplosion*)Explosion)->SetExplosionName("Explosion_Huge");
					CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(Explosion);
					isDead = true;
				}
			}
			else
			{	//���� ����Ǿ��� ��.
				if (LineOnPosPlayerY + 20 > m_CenterPoint.getY() &&
					LineOnPosPlayerY - 30 < m_CenterPoint.getY())
				{
					CObj* Explosion = CObjFactory<CExplosion>::CreateObj(m_CenterPoint.getX(), m_CenterPoint.getY());
					((CExplosion*)Explosion)->SetExplosionName("Explosion_Huge");
					CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(Explosion);
					isDead = true;
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
void CBossBigBullet::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().isExactly(CPlayer::m_Rtti))
	{
		CObj* Explosion = CObjFactory<CExplosion>::CreateObj(m_CenterPoint.getX(), m_CenterPoint.getY());
		((CExplosion*)Explosion)->SetExplosionName("Explosion_Middle");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(Explosion);
		isDead = true;
	}
}

void CBossBigBullet::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 20.f, 20.f);

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_Speed_X = 15.f;
	m_Speed_Y = 10.f;

	//���� ���� ���� ����.
	m_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	SelectedLine = NULL;
	m_CurLine = NULL;

	m_Ani = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_BULLET_1"));
	m_CurFrame = 0;
	m_AniTimer = GetTickCount();
	PlayerIsMyLeft = false;
	isDead = false;

}
int CBossBigBullet::Progress(void)
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
				m_CurFrame = 0;
		}
		return 0;
	}
	else
		return 1;
}
void CBossBigBullet::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, m_CurFrame,
		m_tInfo.fX,
		m_tInfo.fY, PlayerIsMyLeft);

	//Rectangle(_hdc, 
	//	int(m_tInfo.fX - 13), int(m_tInfo.fY - 13),
	//	int(m_tInfo.fX + 13), int(m_tInfo.fY + 13));
}
void CBossBigBullet::Release(void)
{
}
void CBossBigBullet::SetAniName(const TCHAR* _Name)	//�ִϸ��̼� ������.
{
	m_Ani = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_Name);
}
