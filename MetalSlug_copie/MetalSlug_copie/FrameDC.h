#pragma once

class CRc;
class CFrameDC
{
public:
	float FrameWidth;
	float FrameHeight;
public:
	COLORREF m_dwColor;
private:
	CPt m_CenterPoint;
	CRc m_FrameRect;
public:
	const CPt* GetCenterPoint();
	void SetCenterPoint(const CPt& _cp);
	
	const CRc* GetFrameRecv();
	void SetFrameRect(const CRc& _rc);

public:
	void Release();
public:
	CFrameDC();
	CFrameDC(CRc _rc, CPt _pt, DWORD _color);
	~CFrameDC();
};
