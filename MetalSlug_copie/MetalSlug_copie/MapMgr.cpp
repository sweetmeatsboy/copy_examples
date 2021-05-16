#include "stdafx.h"


CMapMgr* CMapMgr::inst = NULL;

CMapMgr* CMapMgr::GetInst()
{
	if (NULL == inst)
		inst = new CMapMgr;
	return inst;
}
void CMapMgr::Release()
{
	for (GetInst()->m_Line_ListPos = GetInst()->m_Line_List.begin();
		GetInst()->m_Line_ListPos != GetInst()->m_Line_List.end(); ++m_Line_ListPos)
	{
		if (*GetInst()->m_Line_ListPos != NULL)
			delete (*GetInst()->m_Line_ListPos);
		(*GetInst()->m_Line_ListPos) = NULL;
	}
	m_Line_List.clear();
}
void CMapMgr::DestroyInst()
{
	if (inst != NULL)
	{
		inst->Release();
		delete inst;
	}
	inst = NULL;
}
void CMapMgr::LoadMapInfo(const char* _mapInfo)
{
	ClearLineMapInfo();

	int Line_List_count = NULL;
	POINT tempLPoint;
	POINT tempRPoint;
	FILE* fp_read;
	int err = fopen_s(&fp_read, _mapInfo, "r");
	if (err != NO_ERROR)
	{
		return;
	}

	CLine* tempInput;

	fscanf_s(fp_read, "%d\n", &Line_List_count);
	for (int i = 0; i < Line_List_count; ++i)
	{
		fscanf_s(fp_read, "%d %d %d %d\n",
			&tempLPoint.x, &tempLPoint.y, &tempRPoint.x, &tempRPoint.y);
		tempInput = new CLine(tempLPoint, tempRPoint);
		m_Line_List.push_back(tempInput);
	}
	if (fp_read != nullptr)
		err = fclose(fp_read);
}
void CMapMgr::ClearLineMapInfo()
{
	for (m_Line_ListPos = m_Line_List.begin();
		m_Line_ListPos != m_Line_List.end(); )
	{
		delete(*m_Line_ListPos);
		(*m_Line_ListPos) = NULL;
		m_Line_ListPos = m_Line_List.erase(m_Line_ListPos);
	}
	m_Line_List.clear();
}

void CMapMgr::AddLine(CLine* _temp)
{
	m_Line_List.push_back(_temp);
}

list<CLine*>* CMapMgr::GetMapLineInfo()
{
	return &m_Line_List;
}
