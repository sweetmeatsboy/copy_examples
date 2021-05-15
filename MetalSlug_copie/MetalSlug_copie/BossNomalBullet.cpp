#include "stdafx.h"

const RTTI CBossNomalBullet::m_Rtti("CBossNomalBullet", CObj::m_Rtti);

void CBossNomalBullet::isOutOfFocus()
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
void CBossNomalBullet::Move()
{
	if (m_Speed_Y < 8)
		m_Speed_Y += 0.15f;

	float _deltaX = m_CenterPoint.getX() + m_Speed_X;
	float _deltaY = m_CenterPoint.getY() + m_Speed_Y;

	SetPos(_deltaX, _deltaY);
}
void CBossNomalBullet::SetAngle(float _fAngle)
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
void CBossNomalBullet::SetBulletType(int  _num)
{
	m_BulletImgType = _num;
	CObj* Target = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();

	int tempDir = 1;
	if (Target->GetCenterPoint().getX() - m_tInfo.fX > 0)
		tempDir = 1;
	else
		tempDir = -1;


	float Distance = abs(Target->GetCenterPoint().getX() - m_tInfo.fX);
	if (Distance >= 0 && Distance < 100)
		m_Speed_X = tempDir * 0.3f;
	if (Distance >= 100 && Distance < 200)
		m_Speed_X = tempDir * 0.5f;
	if (Distance >= 200 && Distance < 300)
		m_Speed_X = tempDir * 0.9f;
	if (Distance >= 300 && Distance < 400)
		m_Speed_X = tempDir * 1.9f;
	if (Distance >= 400 && Distance < 500)
		m_Speed_X = tempDir * 3.5f;

	m_Speed_Y = -8.f;


	if (m_BulletImgType == 1)	//제일 큰 반짝이.
	{
		FrameNumArr[0] = 1;
		FrameNumArr[1] = 2;
		FrameNumArr[2] = 3;
		m_Speed_X += tempDir * 2.f;
	}
	if (m_BulletImgType == 2)
	{
		FrameNumArr[0] = 4;
		FrameNumArr[1] = 5;
		FrameNumArr[2] = 6;
		m_Speed_X += tempDir * 0.9f;
	}
	if (m_BulletImgType == 3)
	{
		FrameNumArr[0] = 7;
		FrameNumArr[1] = 8;
		FrameNumArr[2] = 9;
		m_Speed_X += tempDir * 0.2f;
	}
}
void CBossNomalBullet::CheckLineCollision()
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
					isDead = true;
				}
			}
			else
			{	//선이 변경되었을 때.
				if (LineOnPosPlayerY + 20 > m_CenterPoint.getY() &&
					LineOnPosPlayerY - 30 < m_CenterPoint.getY())
				{
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
void CBossNomalBullet::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().isExactly(CPlayer::m_Rtti))
		isDead = true;
}

void CBossNomalBullet::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 20.f, 20.f);

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_Speed_X = 15.f;
	m_Speed_Y = -25.f;

	//현재 라인 정보 설정.
	m_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	SelectedLine = NULL;
	m_CurLine = NULL;

	m_Ani = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_BULLET"));
	m_CurFrame = 0;
	m_AniTimer = GetTickCount();
	PlayerIsMyLeft = false;
	isDead = false;

	m_BulletImgType = 0;
	memset(FrameNumArr, 0, sizeof(FrameNumArr));

}
int CBossNomalBullet::Progress(void)
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
			if (m_CurFrame >= 3)
				m_CurFrame = 0;
		}
		return 0;
	}
	else
		return 1;
}
void CBossNomalBullet::Render(HDC _hdc)
{
	m_Ani->RenderAniSet(_hdc, FrameNumArr[m_CurFrame],
		m_tInfo.fX,
		m_tInfo.fY, PlayerIsMyLeft);

	//Ellipse(_hdc, 
	//	int(m_tInfo.fX - 3), int(m_tInfo.fY - 3),
	//	int(m_tInfo.fX + 3), int(m_tInfo.fY + 3));
}
void CBossNomalBullet::Release(void)
{
}
