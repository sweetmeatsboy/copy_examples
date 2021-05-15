#include "stdafx.h"


const RTTI CP_H::m_Rtti("CP_H", CPlayerBullet::m_Rtti);
void CP_H::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 20.f, 20.f);

	m_tInfo.fCX = 20;
	m_tInfo.fCY = 20;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_Speed_X = 9.f;
	m_Speed_Y = 9.f;
	m_DeltaCount = 0;		//총알이 이동한 거리를 잴때 사용한다.
	m_isLeft = false;
	m_Ani = CAniInfoMgr::Getinst()->GetPlayer_Weapon_AniSet(_T("P_W_H"));
	isDead = false;

	//현재 라인 정보 설정.
	m_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	SelectedLine = NULL;
	m_CurLine = NULL;

	Atk = 1.f;
}

int CP_H::Progress(void)
{
	if (isDead == false)
	{
		CheckLineCollision();

		m_CenterPoint.setX(m_CenterPoint.getX() + m_Speed_X * cosf(m_fAngle*PI / 180.f));
		m_CenterPoint.setY(m_CenterPoint.getY() - m_Speed_Y * sinf(m_fAngle*PI / 180.f));

		++m_DeltaCount;
		if (m_DeltaCount >= 100)
			return 1;
		SetPos(m_CenterPoint.getX(), m_CenterPoint.getY());
		return 0;
	}
	else
		return 1;
}
void CP_H::Render(HDC _hdc)
{
	m_BulletFrame = m_Ani->GetFrameInfoByIdx(FrameNumber)->m_Frame;

	/*Rectangle(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f));

	Ellipse(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f));*/

	m_Ani->RenderAniSet(_hdc, FrameNumber, m_tInfo.fX, m_tInfo.fY, m_isLeft);
}
void CP_H::Release(void)
{
}
void CP_H::SetAngle(float _Angle)
{
	m_fAngle = _Angle;
	if (m_fAngle >= 0.f&& m_fAngle < 5.5f)
		FrameNumber = 17;
	if (m_fAngle >= 5.5f&& m_fAngle < 11.f)
		FrameNumber = 18;
	if (m_fAngle >= 11.f&& m_fAngle < 16.5f)
		FrameNumber = 19;
	if (m_fAngle >= 16.5f&& m_fAngle < 22.f)
		FrameNumber = 20;
	if (m_fAngle >= 22.f&& m_fAngle < 27.5f)
		FrameNumber = 21;
	if (m_fAngle >= 27.5f&& m_fAngle < 33.f)
		FrameNumber = 22;
	if (m_fAngle >= 33.f&& m_fAngle < 38.5f)
		FrameNumber = 23;
	if (m_fAngle >= 38.5f&& m_fAngle < 44.f)
		FrameNumber = 24;
	if (m_fAngle >= 44.f&& m_fAngle < 49.5f)
		FrameNumber = 25;
	if (m_fAngle >= 49.5f&& m_fAngle < 55.f)
		FrameNumber = 26;
	if (m_fAngle >= 55.f&& m_fAngle < 60.5f)
		FrameNumber = 27;
	if (m_fAngle >= 60.5f&& m_fAngle < 66.f)
		FrameNumber = 28;
	if (m_fAngle >= 66.f&& m_fAngle < 71.5f)
		FrameNumber = 29;
	if (m_fAngle >= 71.5f&& m_fAngle < 77.f)
		FrameNumber = 30;
	if (m_fAngle >= 77.f&& m_fAngle < 82.5f)
		FrameNumber = 31;
	if (m_fAngle >= 82.5f&& m_fAngle < 88.f)
		FrameNumber = 32;
	if (m_fAngle >= 88.f&& m_fAngle < 93.5f)
		FrameNumber = 33;
	if (m_fAngle >= 93.5f&& m_fAngle < 99.f)
		FrameNumber = 33;
	if (m_fAngle >= 99.f&& m_fAngle < 104.5f)
		FrameNumber = 32;
	if (m_fAngle >= 104.5f&& m_fAngle < 110.f)
		FrameNumber = 31;
	if (m_fAngle >= 110.f&& m_fAngle < 115.5f)
		FrameNumber = 30;
	if (m_fAngle >= 115.5f&& m_fAngle < 121.f)
		FrameNumber = 29;
	if (m_fAngle >= 121.f&& m_fAngle < 126.5f)
		FrameNumber = 28;
	if (m_fAngle >= 126.5f&& m_fAngle < 132.f)
		FrameNumber = 27;
	if (m_fAngle >= 132.f&& m_fAngle < 137.5f)
		FrameNumber = 26;
	if (m_fAngle >= 137.5f&& m_fAngle < 143.f)
		FrameNumber = 25;
	if (m_fAngle >= 143.f&& m_fAngle < 148.5f)
		FrameNumber = 24;
	if (m_fAngle >= 148.5f&& m_fAngle < 154.f)
		FrameNumber = 23;
	if (m_fAngle >= 154.f&& m_fAngle < 159.5f)
		FrameNumber = 22;
	if (m_fAngle >= 159.5f&& m_fAngle < 165.f)
		FrameNumber = 21;
	if (m_fAngle >= 165.f&& m_fAngle < 170.5f)
		FrameNumber = 20;
	if (m_fAngle >= 170.5f&& m_fAngle < 176.f)
		FrameNumber = 19;
	if (m_fAngle >= 176.f&& m_fAngle < 181.5f)
		FrameNumber = 18;
	if (m_fAngle >= 181.5f&& m_fAngle < 187.f)
		FrameNumber = 0;
	if (m_fAngle >= 187.f&& m_fAngle < 192.5f)
		FrameNumber = 1;
	if (m_fAngle >= 192.5f&& m_fAngle < 198.f)
		FrameNumber = 2;
	if (m_fAngle >= 198.f&& m_fAngle < 203.5f)
		FrameNumber = 3;
	if (m_fAngle >= 203.5f&& m_fAngle < 208.f)
		FrameNumber = 4;
	if (m_fAngle >= 208.f&& m_fAngle < 213.5f)
		FrameNumber = 5;
	if (m_fAngle >= 213.5f&& m_fAngle < 219.f)
		FrameNumber = 6;
	if (m_fAngle >= 219.f&& m_fAngle < 224.5f)
		FrameNumber = 7;
	if (m_fAngle >= 224.5f&& m_fAngle < 230.f)
		FrameNumber = 8;
	if (m_fAngle >= 230.f&& m_fAngle < 235.5f)
		FrameNumber = 9;
	if (m_fAngle >= 235.5f&& m_fAngle < 241.f)
		FrameNumber = 10;
	if (m_fAngle >= 241.f&& m_fAngle < 246.5f)
		FrameNumber = 11;
	if (m_fAngle >= 246.5f&& m_fAngle < 252.f)
		FrameNumber = 12;
	if (m_fAngle >= 252.f&& m_fAngle < 257.5f)
		FrameNumber = 13;
	if (m_fAngle >= 257.5f&& m_fAngle < 263.f)
		FrameNumber = 14;
	if (m_fAngle >= 263.f&& m_fAngle < 268.5f)
		FrameNumber = 17;
	if (m_fAngle >= 268.5f&& m_fAngle < 274.f)
		FrameNumber = 16;
	if (m_fAngle >= 274.f&& m_fAngle < 279.5f)
		FrameNumber = 15;
	if (m_fAngle >= 279.5f&& m_fAngle < 285.f)
		FrameNumber = 14;
	if (m_fAngle >= 285.f&& m_fAngle < 291.5f)
		FrameNumber = 13;
	if (m_fAngle >= 291.5f&& m_fAngle < 297.f)
		FrameNumber = 12;
	if (m_fAngle >= 297.f&& m_fAngle < 302.5f)
		FrameNumber = 11;
	if (m_fAngle >= 302.5f&& m_fAngle < 308.f)
		FrameNumber = 10;
	if (m_fAngle >= 308.f&& m_fAngle < 313.5f)
		FrameNumber = 9;
	if (m_fAngle >= 313.5f&& m_fAngle < 319.f)
		FrameNumber = 8;
	if (m_fAngle >= 319.f&& m_fAngle < 324.5f)
		FrameNumber = 7;
	if (m_fAngle >= 324.5f&& m_fAngle < 330.f)
		FrameNumber = 6;
	if (m_fAngle >= 330.f&& m_fAngle < 335.5f)
		FrameNumber = 5;
	if (m_fAngle >= 335.5f&& m_fAngle < 341.f)
		FrameNumber = 4;
	if (m_fAngle >= 341.f&& m_fAngle < 346.5f)
		FrameNumber = 3;
	if (m_fAngle >= 346.5f&& m_fAngle < 352.f)
		FrameNumber = 2;
	if (m_fAngle >= 352.f&& m_fAngle < 357.5f)
		FrameNumber = 1;
	if (m_fAngle >= 357.5f&& m_fAngle < 360.f)
		FrameNumber = 0;
}

void CP_H::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().DerivesFrom(CPlayer::m_Rtti) == false)
	{
		isDead = true;
	}
}


void CP_H::CheckLineCollision()
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