#include "stdafx.h"


void CStage_2::Initialize()
{
	MainDC = GetDC(g_hWnd);

	//플레이어 설정.
	if (CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->empty() == true)
	{
		m_pPlayer = CObjFactory<CPlayer>::CreateObj(14400.f, 1750.f);
		CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->push_back(m_pPlayer);
	}
	else
	{
		m_pPlayer = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();
		m_pPlayer->SetPos(14400.f, 1750.f);
		((CPlayer*)m_pPlayer)->SetPosCurPlayer(14400.f, 1750.f);
	}
	m_BackBufferDC = CResourceMgr::GetInst()->GetBitDCMap("Stage_2_BackBuffer")->GetMemDC();
	m_BackGroundDC = CResourceMgr::GetInst()->GetBitDCMap("Stage_2_BackGround")->GetMemDC();

	//카메라 설정부분/
	MapHeight = CResourceMgr::GetInst()->GetBitDCMap("Stage_2_BackGround")->GetBitmapHeight();
	MapWidth = CResourceMgr::GetInst()->GetBitDCMap("Stage_2_BackGround")->GetBitmapWidth();
	m_Cam.SetMapInfo(MapWidth, MapHeight);
	m_Cam.Setfocus(int(m_pPlayer->GetInfo().fX - WINCX / 2.f), int(MapHeight - WINCY));
	CObjMgr::GetInst()->SetCam(&m_Cam);
	////////////////////

	////맵정보 로드 부분
	CMapMgr::GetInst()->ClearLineMapInfo();
	CMapMgr::GetInst()->LoadMapInfo("../MapInfo/Stage_2.LineMapInfo");
	m_Stage_1_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	((CCharacter*)m_pPlayer)->SetLine(m_Stage_1_Line_List);

	//UI관련 부분.
	m_UI = CUIMgr::Getinst();
	m_UI->SetCam(&m_Cam);
	m_UI->SetPlayer((CPlayer*)m_pPlayer);
	m_UI->SetGameState(GAME_IDLE);
	CDevice::GetInstance()->SoundPlay(CDevice::BGM_STAGE_2, 1);

	//보스 테스트 용
	BossWave();
}
void CStage_2::Progress()
{
	CObjMgr::GetInst()->Progress();
	CCollisionMgr::Getinst()->Progress();


	if (m_pPlayer->GetCenterPoint().getX() >= 14000.f)
	{
		m_Cam.Setfocus(int(m_pPlayer->GetCenterPoint().getX() - WINCX / 2.f),
			int(1400.f));
		if (m_pPlayer->GetCenterPoint().getX() < 14050.f)
			m_pPlayer->SetPos(14050.f, m_pPlayer->GetCenterPoint().getY());
	}
	else
		m_Cam.Setfocus(int(m_pPlayer->GetCenterPoint().getX() - WINCX / 2.f),
			int(m_pPlayer->GetCenterPoint().getY() - WINCY / 2.f));
	m_UI->Progress();
}
void CStage_2::Render()
{

	BitBlt(m_BackBufferDC, m_Cam.m_Left_X, m_Cam.m_Left_Y, MapWidth, MapHeight,
		m_BackGroundDC, m_Cam.m_Left_X, m_Cam.m_Left_Y, SRCCOPY);
	//지형지물 그림.
	for (m_LinePos = m_Stage_1_Line_List->begin();
		m_LinePos != m_Stage_1_Line_List->end(); ++m_LinePos)
	{
		(*m_LinePos)->Render(m_BackBufferDC);
	}
	//객체들 그림.
	CObjMgr::GetInst()->Render(m_BackBufferDC);
	TransparentBlt(m_BackBufferDC, 13200, 1220,
		CResourceMgr::GetInst()->GetBitDCMap("Stage_2_FrontGround")->GetBitmapWidth(),
		CResourceMgr::GetInst()->GetBitDCMap("Stage_2_FrontGround")->GetBitmapHeight(),
		CResourceMgr::GetInst()->GetBitDCMap("Stage_2_FrontGround")->GetMemDC(),
		0, 0,
		CResourceMgr::GetInst()->GetBitDCMap("Stage_2_FrontGround")->GetBitmapWidth(),
		CResourceMgr::GetInst()->GetBitDCMap("Stage_2_FrontGround")->GetBitmapHeight(),
		RGB(255, 174, 201));
	m_UI->Render(m_BackBufferDC);

	TransparentBlt(MainDC, 0, 0, WINCX, WINCY,
		m_BackBufferDC,
		m_Cam.m_Left_X, m_Cam.m_Left_Y,
		m_Cam.m_Right_X - m_Cam.m_Left_X,
		m_Cam.m_Right_Y - m_Cam.m_Left_Y, RGB(0, 0, 255));

	//	BitBlt(MainDC, 0, 0, WINCX, WINCY, m_BackBufferDC, m_Cam.m_Left_X, m_Cam.m_Left_Y, SRCCOPY);
}
void CStage_2::BossWave()
{
	if (CDevice::GetInstance()->SoundPlaying(CDevice::BGM_STAGE_2) == true)
		CDevice::GetInstance()->SoundStop(CDevice::BGM_STAGE_2);
	CDevice::GetInstance()->SoundPlay(CDevice::BGM_BOSS, 1);

	TEST = (CBoss*)CObjFactory<CBoss>::CreateObj(14600.f, 2000.f);
	CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(TEST);
}

void CStage_2::Release()
{
	if (CDevice::GetInstance()->SoundPlaying(CDevice::BGM_STAGE_2) == true)
		CDevice::GetInstance()->SoundStop(CDevice::BGM_STAGE_2);
	ReleaseDC(g_hWnd, MainDC);
}