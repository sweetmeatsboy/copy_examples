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
	
	if (ErrorMgr::GetInst().ErrBoxPopupT(_name, _T("file open failed"), hFile == nullptr))
		return;

	DWORD dwColor = 0;
	auto no_error = FileMgr::GetInst().ReadFromFile(hFile, dwColor);
	//ReadFile(hFile, &dwColor, sizeof(DWORD), &dwRead, nullptr);
	m_dwBackColor = dwColor;

	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("loadData"), _T("error - 1"), no_error == false))
		return;

	DWORD cnt = 0;
	//vector<CScene*>::size_type cnt = 0;
	no_error = FileMgr::GetInst().ReadFromFile(hFile, cnt);
	//ReadFile(hFile, &cnt, sizeof(cnt), &dwRead, nullptr);

	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("loadData"), _T("error - 2"), no_error == false))
		return;

	CScene tmpScene;
	for(DWORD i =0; i<cnt; i++)
	{
		LoadScene(hFile, tmpScene);
		m_vScenes.push_back(new CScene(tmpScene));
	}

	//vector<CAnimate*>::size_type cnt2 = 0;
	//ReadFile(hFile, &cnt, sizeof(cnt2), &dwRead, nullptr);
	no_error = FileMgr::GetInst().ReadFromFile(hFile, cnt);

	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("loadData"), _T("error - 3"), no_error == false))
		return;

	CAnimate tmpAni;
	for (vector<CAnimate*>::size_type i = 0; i < cnt; i++)
	{
		LoadAnimate(hFile, tmpAni);
		m_vAnimates.push_back(new CAnimate(tmpAni));
	}

	CloseHandle(hFile);
}

void CSprite::LoadPoint(HANDLE _hFile, CPt& _pt)
{
	//DWORD dwRead = 0;
	CPt::PT_TYPE data = 0;
	
	auto no_err = FileMgr::GetInst().ReadFromFile(_hFile, data);
//	ReadFile(_hFile, &data, sizeof(CPt::PT_TYPE), &dwRead, nullptr);
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("ReadPoint!"), _T("error - 1"), no_err == false ))
		return;

	_pt.setX(data);
	no_err = FileMgr::GetInst().ReadFromFile(_hFile, data = 0);
	//ReadFile(_hFile, &data, sizeof(CPt::PT_TYPE), &dwRead, nullptr);
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("ReadPoint!"), _T("error - 2"), no_err == false))
		return;

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
	DWORD cnt = 0;
	//vector<CRc*>::size_type cnt = 0;
	
	auto no_err = FileMgr::GetInst().ReadFromFile(_hFile, cnt);

	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("LoadScene!"), _T("error - 2"), no_err == false))
		return;

	for (DWORD i = 0; i < cnt; i++)
	{
		rc = CRc(0, 0, 0, 0);
		LoadRect(_hFile, rc);
		_s.pushCollisionRect(rc);
	}
}

void CSprite::LoadAnimate(HANDLE _h, CAnimate& _ani)
{
	_ani.clearScenes();
	DWORD cnt = 0;

	auto no_err = FileMgr::GetInst().ReadFromFile(_h, cnt);
	//ReadFile(_h, &cnt, sizeof(cnt), &dwRead, nullptr);
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("LoadAnimate"), _T("failed"), no_err == false))
		return;

	for (int idx = 0; idx < cnt; idx++)
	{
		//ReadFile(_h, &tmp, sizeof(tmp), &dwRead, nullptr);
		DWORD dwIdx = 0;
		DWORD dwOutputTime = 0;
		no_err = FileMgr::GetInst().ReadFromFile(_h, dwIdx);
		if (ErrorMgr::GetInst().ErrBoxPopupT(_T("Make Scene"), _T("failed"), no_err == false))
			return;
		no_err = FileMgr::GetInst().ReadFromFile(_h, dwOutputTime);
		if (ErrorMgr::GetInst().ErrBoxPopupT(_T("Make Scene"), _T("failed"), no_err == false))
			return;
		_ani.addScene(dwIdx, dwOutputTime);
	}
}