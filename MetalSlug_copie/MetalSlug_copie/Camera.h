#pragma once

//Ä«¸Þ¶ó °´Ã¼.
class CCamera
{
public:
	int m_MapHeight;
	int m_MapWidth;
	int m_Left_X;
	int m_Left_Y;
	int m_Right_X;
	int m_Right_Y;

	bool IsCameraLocked;
	bool IsCamOnTheLine;
public:
	virtual void Setfocus(int _x, int _y);
	virtual void SetMapInfo(int _w, int _h);
public:
	CCamera()
		:m_Left_X(0), m_Left_Y(0), m_Right_X(WINCX), m_Right_Y(WINCY),
		m_MapWidth(0), m_MapHeight(0),
		IsCameraLocked(false), IsCamOnTheLine(false)
	{}
	CCamera(int _x, int _y)
		:m_Left_X(_x), m_Left_Y(_y), m_Right_X(_x + WINCX), m_Right_Y(_y + WINCY),
		m_MapWidth(0), m_MapHeight(0),
		IsCameraLocked(false), IsCamOnTheLine(false)
	{}
	~CCamera() {}
};