#pragma once

class CObj;
class CResourceMgr;
class CLine;
class CUIMgr;
class CCamera;

class CStage_1 : public CSObj
{
private:
	list<CObj*>* m_ObjList[OBJ_END];
	list<CLine*>* m_Stage_1_Line_List;
	list<CLine*>::iterator m_LinePos;
	int LoadingState;
	char LoadingStr[128];

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
	void InsertWave_1();
	void InsertWave_2();
	void InsertWave_3();
	void InsertWave_4();
	void InsertWave_5();
	void InsertWave_6();
	void InsertWave_7();
private:
	bool isWave_1_finished;
	bool isWave_2_finished;
	bool isWave_3_finished;
	bool isWave_4_finished;
	bool isWave_5_finished;
	bool isWave_6_finished;
	bool isWave_7_finished;
public:
	void Initialize();
	void Progress();
	void Render();
	void Release();
public:
	CStage_1() {}
	virtual ~CStage_1()
	{
		Release();
	}
};