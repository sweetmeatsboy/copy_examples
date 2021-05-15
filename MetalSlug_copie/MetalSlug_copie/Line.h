#pragma once

class CLine
{
public:
	POINT m_lPoint, m_rPoint;
	TCHAR tempStr[128];
	float m_Slope;
public:
	virtual void Render(HDC _hdc);
public:
	CLine();
	CLine(POINT _p1, POINT _p2);
	~CLine();
};