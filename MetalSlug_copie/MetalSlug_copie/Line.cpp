#include "stdafx.h"


void CLine::Render(HDC _hdc)
{
	MoveToEx(_hdc, m_lPoint.x, m_lPoint.y, NULL);
	LineTo(_hdc, m_rPoint.x, m_rPoint.y);
}
CLine::CLine()
{
	memset(tempStr, 0, sizeof(tempStr));
}
CLine::CLine(POINT _p1, POINT _p2)
	:m_lPoint(_p1), m_rPoint(_p2)
{
	//점의 왼쪽 오른쪽을 확인 후 swap.
	memset(tempStr, 0, sizeof(tempStr));
	if (m_lPoint.x > m_rPoint.x)
	{
		int temp = m_lPoint.x;
		m_lPoint.x = m_rPoint.x;
		m_rPoint.x = temp;

		temp = m_lPoint.y;
		m_lPoint.y = m_rPoint.y;
		m_rPoint.y = temp;
	}
	if (m_lPoint.x == m_rPoint.x)
	{
		if (m_lPoint.y < m_rPoint.y)
		{
			int temp = m_lPoint.x;
			m_lPoint.x = m_rPoint.x;
			m_rPoint.x = temp;

			temp = m_lPoint.y;
			m_lPoint.y = m_rPoint.y;
			m_rPoint.y = temp;
		}
		m_lPoint.x += -3;	//기울기가 무한대가 되지 않도록 조치.
	}
	m_Slope = ((m_rPoint.y - m_lPoint.y)*1.f) / ((m_rPoint.x - m_lPoint.x)*1.f);
	//만약 직전을 수직으로 생성하려고 한다면 트릭을 써서 기울기가 엄청 높게 나오도록 조정.
}
CLine::~CLine()
{
}