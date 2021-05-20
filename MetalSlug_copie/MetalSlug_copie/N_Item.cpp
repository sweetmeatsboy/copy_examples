#include "stdafx.h"

const RTTI CN_Item::m_Rtti("CN_Item", CObj::m_Rtti);

N_ITEM_TYPE CN_Item::GetNomalItemType()const
{
	return m_N_ITEM_TYPE;
}
void CN_Item::SetNomalItemName(const TCHAR* _Name)
{
	m_CurFrame = 0;

	if (wcscmp(_Name, _T("N_ITEM_CURE")) == 0)
	{
		CountNum = 5;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 32;
		DisapointedTimer = 0;
		Score = 1000;
	}
	if (wcscmp(_Name, _T("N_ITEM_FISH")) == 0)
	{
		CountNum = 3;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 5;
		DisapointedTimer = 1000;
		Score = 1500;
	}
	if (wcscmp(_Name, _T("N_ITEM_BREAD")) == 0)
	{
		CountNum = 3;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 1;
		DisapointedTimer = 1000;
		Score = 500;
	}
	if (wcscmp(_Name, _T("N_ITEM_CAN")) == 0)
	{
		CountNum = 1;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 34;
		DisapointedTimer = 1000;
		Score = 1000;
	}
	if (wcscmp(_Name, _T("N_ITEM_BANANA")) == 0)
	{
		CountNum = 2;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 3;
		DisapointedTimer = 1000;
		Score = 300;
	}
	if (wcscmp(_Name, _T("N_ITEM_CHICKEN")) == 0)
	{
		CountNum = 2;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 14;
		DisapointedTimer = 0;
		Score = 2500;
	}
	if (wcscmp(_Name, _T("N_ITEM_MANDOO")) == 0)
	{
		CountNum = 1;
		m_FirstLoopStartFrame = 0;
		m_FirstLoopEndedFrame = 18;
		DisapointedTimer = 0;
		Score = 100;
	}

	m_Ani = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_ETC_Item_AniSet"), _Name);
	//m_Ani = CAniInfoMgr::Getinst()->Get_ETC_Item_AniSet(_Name);
	m_MaxFrame = m_Ani->GetFrameCount() - 1;
	m_dwFrameTimer = GetTickCount();
}
void CN_Item::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 30.f, 30.f);

	m_fAngle = 0.f;
	m_Speed_X = 0.f;
	m_Speed_Y = 0.f;

	CountNum = 0;	//특정구간 애니메이션 반복횟수를 기록.
	CurCount = 0;
	m_FirstLoopStartFrame = 0;
	m_FirstLoopEndedFrame = 0;
	DisapointedTimer = 0;
	m_Ani = NULL;
	isLastLoop = false;
	isCollision = false;

	Score = 0;
}
int CN_Item::Progress(void)
{
	//애니메이션 재생해야됨.
	if (GetTickCount() - m_dwFrameTimer > m_Ani->GetFrameDelay(m_CurFrame))
	{
		m_dwFrameTimer = GetTickCount();
		++m_CurFrame;
		if (m_CurFrame >= m_Ani->GetFrameCount())
		{
			m_CurFrame = m_Ani->GetFrameCount() - 1;
		}
	}
	if (isCollision == true)
		return 1;
	return 0;
}
void CN_Item::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
		int(m_CenterPoint.getX() - m_tInfo.fCX / 2.f),
		int(m_CenterPoint.getY() - m_tInfo.fCY ),
		int(m_CenterPoint.getX() + m_tInfo.fCX / 2.f),
		int(m_CenterPoint.getY()) );*/

	m_Ani->RenderAniSet(_hdc, m_CurFrame,
		m_CenterPoint.getX(), m_CenterPoint.getY(), false);
}
void CN_Item::Release(void)
{
}
void CN_Item::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().isExactly(CPlayer::m_Rtti))
	{	//점수 이팩트를 띄워줘야 한다.
		//그러면서 아이템도 없애줘야함.
		((CPlayer*)_Something)->AddScore(Score);
		isCollision = true;
	}
}