#include "stdafx.h"



CSceneMgr* CSceneMgr::inst = NULL;

CSceneMgr* CSceneMgr::GetInst()
{
	if (inst == NULL)
	{
		inst = new CSceneMgr();
		inst->m_CurStage = NULL;
	}
	return inst;
}
void CSceneMgr::DestroyInst()
{
	if (inst != NULL)
		Safe_Delete(GetInst()->m_CurStage);
	delete inst;
	inst = NULL;
}
void CSceneMgr::SetStage(STAGE_STATE _stageNum)
{
	if (m_CurStage != NULL)
	{
		delete m_CurStage;
		m_CurStage = NULL;
	}
	switch (_stageNum)
	{
	case STAGE_INTRO:
		GetInst()->m_CurStage = new CStage_Intro();
		GetInst()->m_CurStage->Initialize();
		break;
	case STAGE_1:
		GetInst()->m_CurStage = new CStage_1();
		GetInst()->m_CurStage->Initialize();
		break;
	case STAGE_2:
		GetInst()->m_CurStage = new CStage_2();
		GetInst()->m_CurStage->Initialize();
		break;
	case STAGE_END:
		//			m_CurStage = new CStage_Ending();
		break;
	}
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("SceneMgr"), _T("Stage전환 오류"), GetInst()->m_CurStage == nullptr))
		return;

	//if (GetInst()->m_CurStage == NULL)
	//	MessageBox(g_hWnd, _T("Stage전환 오류"), _T("SceneMgr"), MB_OK);
}
void CSceneMgr::Progress()
{
	GetInst()->m_CurStage->Progress();
}
void CSceneMgr::Render()
{
	GetInst()->m_CurStage->Render();
}
