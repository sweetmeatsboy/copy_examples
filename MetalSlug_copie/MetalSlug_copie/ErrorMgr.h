#pragma once
//g_hwnd �� �������ְ� ��� �ְ� ����.

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

