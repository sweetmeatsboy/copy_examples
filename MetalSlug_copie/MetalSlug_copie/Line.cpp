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
	//���� ���� �������� Ȯ�� �� swap.
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
		m_lPoint.x += -3;	//���Ⱑ ���Ѵ밡 ���� �ʵ��� ��ġ.
	}
	m_Slope = ((m_rPoint.y - m_lPoint.y)*1.f) / ((m_rPoint.x - m_lPoint.x)*1.f);
	//���� ������ �������� �����Ϸ��� �Ѵٸ� Ʈ���� �Ἥ ���Ⱑ ��û ���� �������� ����.
}
CLine::~CLine()
{
}