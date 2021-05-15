#include "stdafx.h"

void CStage_Intro::Initialize()
{
	MainDC = GetDC(g_hWnd);

	memset(LoadingStr, 0, sizeof(LoadingStr));
	swprintf_s(LoadingStr, _T("�ε��� �����մϴ�."));
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
		//��� �ݵ�� LoadAllResource_AtlasMap �� �Ϸ�� �Ŀ� ����Ǿ�� �Ѵ�.
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
		swprintf_s(LoadingStr, _T("Intro �ε���."));
	if (LoadingState == 1)
		swprintf_s(LoadingStr, _T("Stage_1 Resource �ε���."));
	if (LoadingState == 2)
		swprintf_s(LoadingStr, _T("AnimationResource �ε���."));
	if (LoadingState >= 3)
	{
		swprintf_s(LoadingStr, _T("K�� �����ּ���."));
	}
	TextOut(m_BackBufferDC, 0, 20, LoadingStr, _tcslen(LoadingStr));

	BitBlt(MainDC, 0, 0, WINCX, WINCY, m_BackBufferDC, 0, 0, SRCCOPY);
}
void CStage_Intro::Release()
{
	ReleaseDC(g_hWnd, MainDC);
}
