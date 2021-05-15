#pragma once

class CObjMgr
{
private:
	static CObjMgr* inst;
	list<CObj*>			m_ObjList[OBJ_END];
	CCamera* m_Cam;
private:
	CObjMgr()
		:m_Cam(NULL)
	{}
	~CObjMgr() {}
public:
	static CObjMgr* GetInst();
	static void DestroyInst();
public:
	void Progress();
	void Render(HDC _hdc);
	void Release();
	void ClearAllList();
	void ClearListWithoutPlayer();
public:
	list<CObj*>* GetObjList(OBJ_TYPE _type);
	void SetCam(CCamera* _Cam);
	const CCamera* GetCam()const { return m_Cam; }
};