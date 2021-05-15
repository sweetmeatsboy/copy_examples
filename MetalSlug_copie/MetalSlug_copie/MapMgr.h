#pragma once

class CMapMgr
{
private:
	static CMapMgr* inst;
	list<CLine*> m_Line_List;
	list<CLine*>::iterator m_Line_ListPos;
public:
	static CMapMgr* GetInst();
	static void DestroyInst();
public:
	void Release();
public:
	void LoadMapInfo(const char* _mapInfo);
	void ClearLineMapInfo();
	void AddLine(CLine* _temp);
	list<CLine*>* GetMapLineInfo();
};