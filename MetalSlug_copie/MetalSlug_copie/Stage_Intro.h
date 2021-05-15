#pragma once


class CStage_Intro : public CSObj
{
private:
	int LoadingState;
	TCHAR LoadingStr[128];

	HDC MainDC;
	HDC m_BackBufferDC;
	HDC m_BackGroundDC;
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:
	CStage_Intro() {}
	virtual ~CStage_Intro()
	{
		Release();
	}
};