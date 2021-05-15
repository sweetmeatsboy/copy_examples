#pragma once
class CSObj;
class CSceneMgr
{
private:
	static CSceneMgr* inst;
	CSObj* m_CurStage;
private:
	CSceneMgr() {}
	~CSceneMgr() {}
public:
	static CSceneMgr* GetInst();
	static void DestroyInst();
public:
	void SetStage(STAGE_STATE _stageNum);
public:
	void Progress();
	void Render();
};