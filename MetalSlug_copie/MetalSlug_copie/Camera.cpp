#include "stdafx.h"

void CCamera::Setfocus(int _x, int _y)
{
	if (IsCameraLocked)
		return;
	if (IsCamOnTheLine)
		return;
	
	m_Left_X = _x;
	m_Left_Y = _y;

	if (m_Left_X < 0)
		m_Left_X = 0;
	m_Right_X = m_Left_X + WINCX;
	
	if (m_Left_Y < 0)
		m_Left_Y = 0;
	m_Right_Y = m_Left_Y + WINCY;

	if (m_Right_X >= m_MapWidth)
	{
		m_Right_X = m_MapWidth;
		m_Left_X = m_Right_X - WINCX;
	}

	if(m_Right_Y >= m_MapHeight)
	{
		m_Right_Y = m_MapHeight;
		m_Left_Y = m_Right_Y - WINCY;
	}
/*


	if (m_Left_X < 0) 
		m_Left_X = 0;
	if (WINCX < m_MapWidth)
	{
		if (m_Left_X > m_MapWidth - WINCX)
			m_Left_X = m_MapHeight - WINCX;
		m_Right_X = m_Left_X + WINCX;
	}
	else
	{
		m_Right_X = m_Left_X + m_MapWidth;
		m_Left_X = 0;
	}

	if (m_Left_Y < 0)
		m_Left_Y = 0;
	if (WINCY < m_MapHeight)
	{
		if (m_Left_Y > m_MapHeight - WINCY)
			m_Left_Y = m_MapHeight - WINCY;
		m_Right_Y = m_Left_Y + WINCY;
	}
	else
	{
		m_Left_Y = 0;
		m_Right_Y = m_Left_Y + m_MapHeight;
	}*/

}

void CCamera::SetMapInfo(int _w, int _h)
{
	m_MapHeight = _h;
	m_MapWidth = _w;
}