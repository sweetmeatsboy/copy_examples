#pragma once

class FileMgr
{
private :
	static FileMgr* Inst;
public:
	static FileMgr& GetInst()
	{
		if (Inst == nullptr)
			Inst = new FileMgr();
		return *Inst;
	}
public:
	template<typename T>
	bool ReadFromFile(HANDLE _fh, T& _val, DWORD _size = sizeof(T))
	{
		if (_fh == nullptr)
			return false;
		DWORD readCnt;
		auto ret = ReadFile(_fh, &_val, _size, &readCnt, nullptr);
		if (_size != readCnt)
			return false;
		return true;
	}
};
