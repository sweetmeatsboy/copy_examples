#pragma once

class CFrameDC;

class CAniDCSet
{
public:
	struct FrameInfo
	{
		CFrameDC* m_Frame;
		DWORD m_FrameTimer;
	};
	HDC m_TempDC;
	HDC m_MainDC;
	HBITMAP m_TempBitMap;
private:

	float m_Scale_X;
	float m_Scale_Y;

	vector<FrameInfo*> m_FrameInfo;
	TCHAR AniName[128];
	int m_MaxFrameCnt;
	int m_CurFrameIdx;
	DWORD m_dwFrameTimer;
	string m_AtlasMapName;

public:

	const FrameInfo* GetFrameInfoByIdx(int _idx) const;
	const int GetCurFrameIdx() const {
		return m_CurFrameIdx;
	}
	void SetAniName(const TCHAR* _name);
	const TCHAR* GetName()const;
	void AddFrameInfo(CFrameDC* _fdc, DWORD _timeInfo);
	int GetFrameCount() const;
	void RenderAniSet(HDC _hdc, int _durName, float _cx, float _cy, bool _isReverse);
	DWORD GetFrameDelay(int _curFrame) const 
	{
		return m_FrameInfo.at(_curFrame)->m_FrameTimer;
	}
	void SetAtlasMapName(string _tmp);
	void SetScale(float _x, float _y)
	{
		m_Scale_X = _x;
		m_Scale_Y = _y;
	}

public:
	void Release();
public:
	CAniDCSet()
	{
		ZeroMemory(AniName, sizeof(AniName));
		m_AtlasMapName.clear();

		m_Scale_X = m_Scale_Y = 1.f;
		m_MainDC = GetDC(g_hWnd);
		m_TempDC = CreateCompatibleDC(m_MainDC);
		m_TempBitMap = CreateCompatibleBitmap(m_MainDC, WINCX, WINCY);
		SelectObject(m_TempDC, m_TempBitMap);
		ReleaseDC(g_hWnd, m_MainDC);
		DeleteObject(m_TempBitMap);
	}
	~CAniDCSet()
	{
		Release();
	}
};