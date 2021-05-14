#pragma once


class CBitmapDC
{
private:
	HDC m_MemDC;
	HBITMAP m_hBitMap;
	BITMAP m_BitmapInfo;
	TCHAR tempStr[128];
private :
	void CheckResource();
	void ErrMsg(const TCHAR* _err1, const TCHAR* _err2);
public:
	void LoadImg(const TCHAR* _imgPath);
	CBitmapDC* GetCBitMapDC()
	{
		return this;
	}
	HDC GetMemDC()
	{
		return m_MemDC;
	}
	HBITMAP GetBitmap()
	{
		return m_hBitMap;
	}
	BITMAP GetBitmapInfo()
	{
		return m_BitmapInfo;
	}
	int GetBitmapWidth()
	{
		return m_BitmapInfo.bmWidth;
	}
	CBitmapDC* CreateBuffer(int _x, int _y);
public:
	virtual void Release();
public:
	CBitmapDC();
	CBitmapDC(const TCHAR* _imgPath);
	virtual ~CBitmapDC();
};