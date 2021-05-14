#include "stdafx.h"

void CBitmapDC::CheckResource()
{
	g_hdc = GetDC(g_hWnd);
	if (m_MemDC != nullptr)
		DeleteDC(m_MemDC);
	if (m_hBitMap != nullptr)
		DeleteObject(m_hBitMap);
	m_MemDC = CreateCompatibleDC(g_hdc);
}

void CBitmapDC::ErrMsg(const TCHAR* _err1, const TCHAR* _err2)
{
	_stprintf(tempStr, _err1);
	MessageBox(g_hWnd, tempStr, _err2, MB_OK);
}


void CBitmapDC::LoadImg(const TCHAR* _imgPath)
{
	CheckResource();

	m_hBitMap = (HBITMAP)LoadImage(nullptr, _imgPath, IMAGE_BITMAP,
		0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);

	if (m_hBitMap == nullptr)
	{

		ErrMsg(_T("이미지 읽기 실패"), _T("CBitmapDC"));
		return;
	}
	else
		GetObject(m_hBitMap, sizeof(BITMAP), &m_BitmapInfo);
	SelectObject(m_MemDC, m_hBitMap);
}


CBitmapDC* CBitmapDC::CreateBuffer(int _x, int _y)
{
	this->CheckResource();

	m_hBitMap = CreateCompatibleBitmap(g_hdc, _x, _y);
	SelectObject(m_MemDC, m_hBitMap);
	GetObject(m_hBitMap, sizeof(BITMAP), &m_BitmapInfo);

	HDC tempDC = CreateCompatibleDC(g_hdc);
	HBITMAP tempH = (HBITMAP)LoadImage(NULL, _T("../Texture/BackBuffer.bmp")
		, IMAGE_BITMAP, 0, 0
		, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_CREATEDIBSECTION);
	if (tempH == nullptr)
	{
		ErrMsg(_T("버퍼생성 실패"), _T("CBitmapDC"));
		return nullptr;
	}

	SelectObject(tempDC, tempH);
	BITMAP tempInfo;
	GetObject(tempH, sizeof(BITMAP), &tempInfo);

	StretchBlt(m_MemDC, 0, 0, _x, _y, tempDC
		, 0, 0, tempInfo.bmWidth, tempInfo.bmHeight, SRCCOPY);
	return this;
}

void CBitmapDC::Release()
{
	DeleteDC(m_MemDC);
	DeleteObject(m_hBitMap);
}


CBitmapDC::CBitmapDC()
{
	m_MemDC = nullptr;
	m_hBitMap = nullptr;
	ZeroMemory(tempStr, sizeof(tempStr));
}
CBitmapDC::CBitmapDC(const TCHAR* _imgPath)
{
	CBitmapDC();
	LoadImg(_imgPath);
}
CBitmapDC::~CBitmapDC()
{
	Release();
}
