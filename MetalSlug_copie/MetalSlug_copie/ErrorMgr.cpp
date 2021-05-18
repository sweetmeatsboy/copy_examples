#include "stdafx.h"

ErrorMgr* ErrorMgr::Inst = nullptr;

ErrorMgr& ErrorMgr::GetInst()
{
	if (Inst == nullptr)
		Inst = new ErrorMgr();
	return *Inst;
}


void ErrorMgr::Init(HWND _h)
{
	Inst->mHwnd = _h;
}

bool ErrorMgr::ErrBoxPopupT(const TCHAR* _caption, const TCHAR* _con, bool _flag)
{
	if (mHwnd == nullptr)
		return false;
	if(_flag)
		MessageBox(mHwnd, _con, _caption, MB_OK);
	return _flag;
}
