#include "stdafx.h"


CObjMgr* CObjMgr::inst = NULL;
CObjMgr* CObjMgr::GetInst()
{
	if (inst == NULL)
	{
		inst = new CObjMgr();
		inst->m_Cam = NULL;
	}
	return inst;
}
void CObjMgr::DestroyInst()
{
	GetInst()->Release();
}
void CObjMgr::Progress()
{
	static int padding = 300;
	int camLX = m_Cam->m_Left_X;
	int camRX = m_Cam->m_Right_X;
	int camLY = m_Cam->m_Left_Y;
	int camRY = m_Cam->m_Right_Y;

	for (int idx = 0; idx < OBJ_END; ++idx)
	{
		auto objList = m_ObjList[idx];
		for (list<CObj*>::iterator pos = objList.begin();
			pos != objList.end(); )
		{
			float x = (*pos)->GetCenterPoint().getX();
			float y = (*pos)->GetCenterPoint().getY();
			if (x > camLX - padding && x < camRX + padding && y > camLY - padding && y < camRY + padding)
			{
				if ((*pos)->Progress() == 1)
				{
					delete (*pos);
					(*pos) = NULL;
					pos = objList.erase(pos);
				}
				else
					++pos;
			}
			else
				++pos;
		}
	}
}
void CObjMgr::Render(HDC _hdc)
{
	for (int y = 0; y < OBJ_END; ++y)
	{
		for (list<CObj*>::iterator pos = m_ObjList[y].begin();
			pos != m_ObjList[y].end(); ++pos)
		{
			if ((*pos)->GetInfo().fX > m_Cam->m_Left_X - 300
				&& (*pos)->GetInfo().fX < m_Cam->m_Right_X + 300
				&& (*pos)->GetInfo().fY > m_Cam->m_Left_Y - 200
				&& (*pos)->GetInfo().fY < m_Cam->m_Right_Y + 200)
			{
				(*pos)->Render(_hdc);
			}
		}
	}
}
void CObjMgr::Release()
{
	m_Cam = NULL;
	ClearAllList();
	if (inst != NULL)
		delete inst;
	inst = NULL;
}
void CObjMgr::ClearAllList()
{
	for (int y = 0; y < OBJ_END; ++y)
	{
		for (list<CObj*>::iterator pos = m_ObjList[y].begin();
			pos != m_ObjList[y].end(); )
		{
			delete (*pos);
			(*pos) = NULL;
			pos = m_ObjList[y].erase(pos);
		}
		m_ObjList[y].clear();
	}
}
void CObjMgr::ClearListWithoutPlayer()
{
	for (int y = 0; y < OBJ_END; ++y)
	{
		if (y != OBJ_PLAYER)
		{
			for (list<CObj*>::iterator pos = m_ObjList[y].begin();
				pos != m_ObjList[y].end(); )
			{
				delete (*pos);
				(*pos) = NULL;
				pos = m_ObjList[y].erase(pos);
			}
			m_ObjList[y].clear();
		}
	}
}


list<CObj*>* CObjMgr::GetObjList(OBJ_TYPE _type)
{
	return &(GetInst()->m_ObjList[_type]);
}
void CObjMgr::SetCam(CCamera* _Cam)
{
	m_Cam = _Cam;
}
