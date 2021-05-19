#include "stdafx.h"


const CPt* CFrameDC::GetCenterPoint()
{
	return &m_CenterPoint;
}

void CFrameDC::SetCenterPoint(const CPt& _pt)
{
	m_CenterPoint = _pt;
}

const CRc* CFrameDC::GetFrameRect()
{
	return &m_FrameRect;
}

void CFrameDC::SetFrameRect(const CRc& _rc)
{
	m_FrameRect = _rc;
}

void CFrameDC::Release()
{
}

CFrameDC::CFrameDC()
	: m_dwColor(0)
{
}

CFrameDC::CFrameDC(CRc _rc, CPt _pt, DWORD _color)
	: m_dwColor(_color)
{
	SetFrameRect(_rc);
	SetCenterPoint(_pt);
	FrameWidth = m_FrameRect.getWidth();
	FrameHeight = m_FrameRect.getHeight();
}

CFrameDC::~CFrameDC()
{
	Release();
}