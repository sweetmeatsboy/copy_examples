#include "stdafx.h"


CMainGame::CMainGame(void)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize(void)
{
	CSceneMgr::GetInst()->SetStage(STAGE_INTRO);
	CCollisionMgr::Getinst();
	CObjMgr::GetInst();
	CAniInfoMgr::Getinst();
	CResourceMgr::GetInst();

	CDevice::GetInstance();
	
	FileMgr::GetInst();
	ErrorMgr::GetInst().Init(g_hWnd);
}

void CMainGame::Progress(void)
{
	CSceneMgr::GetInst()->Progress();
}

void CMainGame::Render(void)
{
	CSceneMgr::GetInst()->Render();
}

void CMainGame::Release(void)
{
	CSceneMgr::DestroyInst();
	CCollisionMgr::DestroyInst();
	CObjMgr::DestroyInst();
	CAniInfoMgr::DestroyInst();
	CResourceMgr::DestroyInst();

	CDevice::GetInstance()->DestroyInst();

}