#pragma once

class CBitmapDC;

class CResourceMgr
{
private:
	static CResourceMgr* inst;
	map<string, CBitmapDC*> m_BitDCMap;

	void SetBitMap(const char* _key, const TCHAR* _path);
public:
	CResourceMgr() {}
	~CResourceMgr() {}

	void LoadResource_Intro();
	void LoadResource_Bullet();
	void LoadResource_Stage_1();
	void LoadResource_Stage_2();
	void LoadResource_AtlasMap();
	void ReleaseAllResource();
	CBitmapDC* GetBitDCMap(string _str);
public:
	static CResourceMgr* GetInst()
	{
		if (inst != nullptr)
			return inst;
		inst = new CResourceMgr();
		inst->m_BitDCMap;
		return inst;
	}
	static void DestroyInst()
	{
		inst->ReleaseAllResource();
		Safe_Delete(inst);
	}
};


