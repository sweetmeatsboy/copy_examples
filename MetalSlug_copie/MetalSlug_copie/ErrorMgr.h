#pragma once
//g_hwnd 걍 지정해주고 들고 있게 하자.

class ErrorMgr
{
private:
	static ErrorMgr* Inst;
private:
	HWND mHwnd;
private:
	ErrorMgr() { mHwnd = nullptr; }

public:
	static ErrorMgr& GetInst();
	static void Init(HWND _h);
public:
	bool ErrBoxPopupT(const TCHAR* _caption, const TCHAR* _con, bool _flag);
};

