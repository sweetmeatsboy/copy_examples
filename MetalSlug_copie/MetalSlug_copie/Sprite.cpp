#include "stdafx.h"

extern HWND g_hMainDlg;

CSprite::CSprite()
	: m_hImageDC(nullptr), m_hOutputDC(nullptr), m_ptCur(), m_rcCur(), m_dwBackColor(0)
{
}

CSprite::~CSprite()
{
	if (m_hImageDC != nullptr)
	{
		DeleteDC(m_hImageDC);
		m_hImageDC = nullptr;
	}

	if (m_hOutputDC)
	{
		SelectObject(m_hOutputDC, m_hOldBrush);
		DeleteObject(m_hBrush);
		DeleteDC(m_hOutputDC);
		m_hOutputDC = nullptr;
	}
}

void CSprite::LoadData(const TCHAR* _name)
{
	DWORD dwRead = 0;
	HANDLE hFile = CreateFile(_name, GENERIC_READ
		, 0, 0, OPEN_EXISTING, 0, nullptr);
	if (hFile == nullptr)
	{
		MessageBox(g_hWnd, _T("파일개방오류"), _T("오류"), MB_OK);
		return;
	}

	DWORD dwColor = 0;
	ReadFile(hFile, &dwColor, sizeof(DWORD), &dwRead, nullptr);
	m_dwBackColor = dwColor;

	if (dwRead != sizeof(DWORD))
	{
		MessageBox(g_hWnd, _T("loadData() error!"), _T("오류"), MB_OK);
		return;
	}

	vector<CScene*>::size_type cnt = 0;
	ReadFile(hFile, &cnt, sizeof(cnt), &dwRead, nullptr);

	if (dwRead != sizeof(cnt))
	{
		MessageBox(g_hWnd, _T("loadData() error!"), _T("오류"), MB_OK);
		return;
	}

	CScene tmpScene;
	for(vector<CScene*>::size_type i =0; i<cnt; i++)
	{
		LoadScene(hFile, tmpScene);
		m_vScenes.push_back(new CScene(tmpScene));
	}

	vector<CAnimate*>::size_type cnt2 = 0;
	ReadFile(hFile, &cnt, sizeof(cnt2), &dwRead, nullptr);

	if (dwRead != sizeof(cnt2))
	{
		MessageBox(g_hWnd, _T("loadData() error2!"), _T("오류"), MB_OK);
		return;
	}

	CAnimate tmpAni;
	for (vector<CAnimate*>::size_type i = 0; i < cnt2; i++)
	{
		LoadAnimate(hFile, tmpAni);
		m_vAnimates.push_back(new CAnimate(tmpAni));
	}

	CloseHandle(hFile);
}

void CSprite::LoadPoint(HANDLE _hFile, CPt& _pt)
{
	DWORD dwRead = 0;
	CPt::PT_TYPE data = 0;

	ReadFile(_hFile, &data, sizeof(CPt::PT_TYPE), &dwRead, nullptr);
	if (sizeof(CPt::PT_TYPE) != dwRead)
	{
		MessageBox(g_hWnd, _T("ReadPoint() error _1"), _T("오류"), MB_OK);
		return;
	}

	_pt.setX(data);

	ReadFile(_hFile, &data, sizeof(CPt::PT_TYPE), &dwRead, nullptr);
	if (sizeof(CPt::PT_TYPE) != dwRead)
	{
		MessageBox(g_hWnd, _T("ReadPoint() error _2"), _T("오류"), MB_OK);
		return;
	}

	_pt.setY(data);
}

void CSprite::LoadRect(HANDLE _hFile, CRc& _rc)
{
	CPt pt;

	LoadPoint(_hFile, pt);
	_rc.setPoint2(pt);

	pt = CPt(0, 0);

	LoadPoint(_hFile, pt);
	_rc.setPoint1(pt);
}

void CSprite::LoadScene(HANDLE _hFile, CScene& _s)
{
	CPt pt;
	CRc rc;

	_s.clearCollisionRect();

	LoadRect(_hFile, rc);
	_s.setMainRect(rc);

	LoadPoint(_hFile, pt);
	_s.setMainPoint(pt);

	DWORD dwRead = 0;
	vector<CRc*>::size_type cnt = 0;

	ReadFile(_hFile, &cnt, sizeof(cnt), &dwRead, nullptr);

	if (dwRead != sizeof(cnt))
	{
		MessageBox(g_hWnd, _T("LoadScene() error!"), _T("오류"), MB_OK);
		return;
	}

	for (int i = 0; i < cnt; i++)
	{
		rc = CRc(0, 0, 0, 0);
		LoadRect(_hFile, rc);
		_s.pushCollisionRect(rc);
	}
}

void CSprite::LoadAnimate(HANDLE _h, CAnimate& _ani)
{
	_ani.clearScenes();
	int cnt = 0;
	int idx = 0;

	DWORD dwRead = 0;
	ReadFile(_h, &cnt, sizeof(cnt), &dwRead, nullptr);

	CAnimate::tagScene tmp;
	for (idx = 0; idx < cnt; idx++)
	{
		ReadFile(_h, &tmp, sizeof(tmp), &dwRead, nullptr);
		_ani.addScene(tmp.m_dwIndex, tmp.m_dwOutputTime);
	}
}