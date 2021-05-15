#include "stdafx.h"

void CStage_Intro::Initialize()
{
	MainDC = GetDC(g_hWnd);

	memset(LoadingStr, 0, sizeof(LoadingStr));
	swprintf_s(LoadingStr, _T("로딩을 시작합니다."));
	LoadingState = 0;

	CDevice::GetInstance()->SoundPlay(CDevice::BGM_INTRO, 0);

}
void CStage_Intro::Progress()
{
	if (LoadingState == 0)
	{
		CResourceMgr::GetInst()->LoadResource_Intro();
		CResourceMgr::GetInst()->LoadResource_Bullet();

		m_BackBufferDC = CResourceMgr::GetInst()->GetBitDCMap("IntroBackBuffer")->GetMemDC();
		m_BackGroundDC = CResourceMgr::GetInst()->GetBitDCMap("IntroBackGround")->GetMemDC();
	}
	if (LoadingState == 1)
	{
		CResourceMgr::GetInst()->LoadResource_Stage_1();
		CResourceMgr::GetInst()->LoadResource_Stage_2();
	}
	if (LoadingState == 2)
	{
		CResourceMgr::GetInst()->LoadResource_AtlasMap();
		//얘는 반드시 LoadAllResource_AtlasMap 가 완료된 후에 수행되어야 한다.
		CAniInfoMgr::Getinst()->LoadResource_Animation();
	}
	if (LoadingState == 3)
	{
		if (GetAsyncKeyState('K'))
		{
			if (CDevice::GetInstance()->SoundPlaying(CDevice::BGM_INTRO) == true)
				CDevice::GetInstance()->SoundStop(CDevice::BGM_INTRO);
			CSceneMgr::GetInst()->SetStage(STAGE_1);
		}
	}
	if (LoadingState < 3)
		++LoadingState;

}
void CStage_Intro::Render()
{
	BitBlt(m_BackBufferDC, 0, 0, WINCX, WINCY,
		m_BackGroundDC, 0, 0, SRCCOPY);
	memset(LoadingStr, 0, sizeof(LoadingStr));

	if (LoadingState == 0)
		swprintf_s(LoadingStr, _T("Intro 로딩중."));
	if (LoadingState == 1)
		swprintf_s(LoadingStr, _T("Stage_1 Resource 로딩중."));
	if (LoadingState == 2)
		swprintf_s(LoadingStr, _T("AnimationResource 로딩중."));
	if (LoadingState >= 3)
	{
		swprintf_s(LoadingStr, _T("K를 눌러주세요."));
	}
	TextOut(m_BackBufferDC, 0, 20, LoadingStr, _tcslen(LoadingStr));

	BitBlt(MainDC, 0, 0, WINCX, WINCY, m_BackBufferDC, 0, 0, SRCCOPY);
}
void CStage_Intro::Release()
{
	ReleaseDC(g_hWnd, MainDC);
}
