#pragma once

class CSprite
{
private:
	CPt m_ptCur;
	CRc m_rcCur;

	HDC m_hImageDC;
	HDC m_hOutputDC;
	HBRUSH m_hBrush;
	HBRUSH m_hOldBrush;
	INT m_iImageWidth;
	INT m_iImageHeight;

private:
	CSprite(const CSprite& _other);
	void operator = (const CSprite& _other);
public:
	CSprite();
	~CSprite();

	void LoadPoint(HANDLE _h, CPt& _pt);
	void LoadRect(HANDLE _h, CRc& _rc);
	void LoadScene(HANDLE _h, CScene& _s);
	void LoadAnimate(HANDLE _h, CAnimate& _other);
	void LoadData(const TCHAR* _strFileName);
public:
	DWORD m_dwBackColor;
	vector<CScene*> m_vScenes;
	vector<CAnimate*> m_vAnimates;
};
