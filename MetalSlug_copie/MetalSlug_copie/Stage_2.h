#pragma once
class CUIMgr;
class CCamera;
class CLine;
class CBoss;

class CStage_2 : public CSObj
{
private:
	//TurretTEST¿ë.
	CBoss * TEST;
private:
	list<CObj*>* m_ObjList[OBJ_END];
	list<CLine*>* m_Stage_1_Line_List;
	list<CLine*>::iterator m_LinePos;

	CObj* m_pPlayer;

	HDC MainDC;
	HDC m_BackBufferDC;
	HDC m_BackGroundDC;
	HDC m_UIMemDC;

	CUIMgr* m_UI;
	CCamera m_Cam;

	int MapHeight;
	int MapWidth;
private:
	void BossWave();
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:
	CStage_2() {}
	virtual ~CStage_2()
	{
		Release();
	}
};