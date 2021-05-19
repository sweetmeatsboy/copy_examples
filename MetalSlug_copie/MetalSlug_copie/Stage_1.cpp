#include "stdafx.h"


void CStage_1::Initialize()
{
	MainDC = GetDC(g_hWnd);
	float startX = 100.f;
	float startY = 1700.f;
	//플레이어 설정.
	if (CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->empty() == true)
	{
		m_pPlayer = CObjFactory<CPlayer>::CreateObj(startX, startY);
		CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->push_back(m_pPlayer);
	}
	m_pPlayer = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();
	m_pPlayer->SetPos(startX, startY);
//	((CPlayer*)m_pPlayer)->SetPosCurPlayer(100.f, 1700.f);

	m_BackBufferDC = CResourceMgr::GetInst()->GetBitDCMap("Stage_1_BackBuffer")->GetMemDC();
	m_BackGroundDC = CResourceMgr::GetInst()->GetBitDCMap("Stage_1_BackGround")->GetMemDC();

	//카메라 설정부분/
	MapHeight = CResourceMgr::GetInst()->GetBitDCMap("Stage_1_BackGround")->GetBitmapHeight();
	MapWidth = CResourceMgr::GetInst()->GetBitDCMap("Stage_1_BackGround")->GetBitmapWidth();
	m_Cam.SetMapInfo(MapWidth, MapHeight);
	m_Cam.Setfocus(int(m_pPlayer->GetInfo().fX - WINCX / 2.f), int(MapHeight - WINCY));
	CObjMgr::GetInst()->SetCam(&m_Cam);
	memset(LoadingStr, 0, sizeof(LoadingStr));
	////////////////////

	////맵정보 로드 부분
	CMapMgr::GetInst()->ClearLineMapInfo();
	CMapMgr::GetInst()->LoadMapInfo("../MapInfo/Stage_1.LineMapInfo");
	m_Stage_1_Line_List = CMapMgr::GetInst()->GetMapLineInfo();
	((CCharacter*)m_pPlayer)->SetLine(m_Stage_1_Line_List);


	m_UI = CUIMgr::Getinst();
	m_UI->SetCam(&m_Cam);
	m_UI->SetPlayer((CPlayer*)m_pPlayer);

	//배경 관련된 오브젝트들 삽입.
	CObj* FrontGround = CObjFactory<CFrontGroundObject>::CreateObj(500.f, 2035.f);
	((CFrontGroundObject*)FrontGround)->SetObjectAni(_T("STAGE_1_FRONT_OBJ_1"));
	CObjMgr::GetInst()->GetObjList(OBJ_OBJECT)->push_back(FrontGround);

	FrontGround = CObjFactory<CFrontGroundObject>::CreateObj(1218.f, 2016.f);
	((CFrontGroundObject*)FrontGround)->SetObjectAni(_T("STAGE_1_FRONT_OBJ_2"));
	CObjMgr::GetInst()->GetObjList(OBJ_OBJECT)->push_back(FrontGround);

	CObj* Rock = CObjFactory<CRock_1>::CreateObj(2100.f, 1861.f);
	CObjMgr::GetInst()->GetObjList(OBJ_ITEM)->push_back(Rock);

	CObj* Door_1 = CObjFactory<CDoor>::CreateObj(7080.f, 380.f);
	CObjMgr::GetInst()->GetObjList(OBJ_OBJECT)->push_back(Door_1);

	FrontGround = CObjFactory<CFrontGroundObject>::CreateObj(7080.f, 400.f);
	((CFrontGroundObject*)FrontGround)->SetObjectAni(_T("STAGE_1_FRONT_DOOR_2"));
	CObjMgr::GetInst()->GetObjList(OBJ_OBJECT)->push_back(FrontGround);

	isWave_1_finished = false;
	isWave_2_finished = false;
	isWave_3_finished = false;
	isWave_4_finished = false;
	isWave_5_finished = false;
	isWave_6_finished = false;
	isWave_7_finished = false;

	CDevice::GetInstance()->SoundPlay(CDevice::BGM_STAGE_1, 1);
	//플레이어가 x좌표 7110을 넘어가면 스테입지 전환을 해줘야 한다.
}
void CStage_1::Progress()
{
	CObjMgr::GetInst()->Progress();
	CCollisionMgr::Getinst()->Progress();
	float mX = m_pPlayer->GetCenterPoint().getX();
	float mY = m_pPlayer->GetCenterPoint().getY();
	auto monsterListEmpty = CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->empty();
	if (mX  >= 0 && mX  < 400)
	{
		InsertWave_1();
		InsertWave_2();
		InsertWave_3();
		InsertWave_4();
		InsertWave_5();
		InsertWave_6();
		InsertWave_7();
		m_Cam.Setfocus(int(mX  - WINCX / 2.f), 1400);
	}
	if (mX  >= 400 && mX  < 1200)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(400, 1400);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), 1400);
	}
	if (mX  >= 1200 && mX  < 2100)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(400, 1400);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), 1400);
	}
	if (mX  >= 2100 && mX  < 2300)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(2100, 1430);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), 1430);
	}
	if (mX  >= 2300 && mX  < 2962)
	{
		m_Cam.Setfocus(int(mX  - WINCX / 2.f), int(mY - WINCY / 2.f - 150));
	}
	if (mX  >= 2962 && mX  < 3700)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(2962, 800);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), 800);
	}
	if (mX  >= 3700 && mX  < 4260.f)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(3700, 800);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), int(mY - WINCY / 2.f) - 250);
	}
	if (mX  >= 4260.f && mX  < 4780)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(4260, 570);
	}
	if (mX  >= 4780.f && mX  < 5900.f)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(4700, 570);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), 570.f);
	}

	if (mX  >= 5900.f)
	{
		if (monsterListEmpty == false)	//구간 내 모든 적군 처리
			m_Cam.Setfocus(5900, 70);
		else
			m_Cam.Setfocus(int(mX  - WINCX / 2.f), 0);
	}
	else
	{
		m_Cam.Setfocus(int(mX  - WINCX / 2.f), int(mY - WINCY / 2.f));
	}
	m_UI->Progress();

	if (mX  >= 7110.f)
		CSceneMgr::GetInst()->SetStage(STAGE_2);

}
void CStage_1::Render()
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

	m_UI->Render(m_BackBufferDC);

	TransparentBlt(MainDC, 0, 0, WINCX, WINCY,
		m_BackBufferDC,
		m_Cam.m_Left_X, m_Cam.m_Left_Y,
		m_Cam.m_Right_X - m_Cam.m_Left_X,
		m_Cam.m_Right_Y - m_Cam.m_Left_Y, RGB(0, 0, 255));

	//	BitBlt(MainDC, 0, 0, WINCX, WINCY, m_BackBufferDC, m_Cam.m_Left_X, m_Cam.m_Left_Y, SRCCOPY);
}
void CStage_1::Release()
{
	if (CDevice::GetInstance()->SoundPlaying(CDevice::BGM_STAGE_1) == true)
		CDevice::GetInstance()->SoundStop(CDevice::BGM_STAGE_1);
	ReleaseDC(g_hWnd, MainDC);
}

void CStage_1::InsertWave_1()
{
	if (isWave_1_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj(500.f, 1855.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_104"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_32"));
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_CURE"));
		//((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_F"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CHelper>::CreateObj(400.f, 1855.f);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CHelper*)temp)->InsertWeaonItem(_T("W_ITEM_F"));
		//((CHelper*)temp)->InsertNomalItem(_T("N_ITEM_BREAD"));
		CObjMgr::GetInst()->GetObjList(OBJ_NPC)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj(650.f, 1855.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_10"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_33"));
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_F"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_1_finished = true;
	}

}
void CStage_1::InsertWave_2()
{
	if (isWave_2_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(1700.f, 1855.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_9"));
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_H"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_36"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(1820.f, 1855.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_51"));
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_FISH"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_30"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(1930.f, 1855.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_17"));
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_MANDOO"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_15"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_32"));
		//((CSoldier*)temp)->InsertNomalItem(N_ITEM_BANANA);
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);


		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(2050.f, 1855.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_CHICKEN"));
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_18"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_33"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_2_finished = true;
	}
}
void CStage_1::InsertWave_3()
{
	if (isWave_3_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(2400.f, 1610.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_CAN"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_38"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_3_finished = true;
	}
}
void CStage_1::InsertWave_4()
{
	if (isWave_4_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(3180.f, 1360.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_BANANA"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_34"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(3300.f, 1320.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertNomalItem(_T("N_ITEM_CURE"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_40"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(3450.f, 1300.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_41"));
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_RELOAD_BOMB"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(3600.f, 1260.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_32"));
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_S"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_4_finished = true;
	}
}
void CStage_1::InsertWave_5()
{
	if (isWave_5_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(4070.f, 1200.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_9"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_F"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_29"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(4250.f, 1080.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_F"));
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_11"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_33"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(4330.f, 1000.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_F"));
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_12"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_36"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_5_finished = true;
	}

}
void CStage_1::InsertWave_6()
{
	if (isWave_6_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(4870.f, 830.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_18"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_36"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(5000.f, 800.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_13"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_40"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(5200.f, 760.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_4"));
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_RELOAD_BOMB"));
		((CSoldier*)temp)->InsertReactionSoldier(_T("Reaction_14"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_42"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(5340.f, 720.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertWeaonItem(_T("W_ITEM_RELOAD_BULLET"));
		((CSoldier*)temp)->InsertExtraSoldier(_T("Extra_10"));
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_29"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(5063.f, 417.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_30"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_6_finished = true;
	}

}
void CStage_1::InsertWave_7()
{
	if (isWave_7_finished == false)
	{
		CObj* temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(6230.f, 510.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_29"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(6360.f, 510.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_42"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);

		temp = CObjFactory<CSoldier>::CreateObj();
		temp->SetPos(6500.f, 510.f);
		((CSoldier*)temp)->SetTarget(m_pPlayer);
		((CCharacter*)temp)->SetLine(m_Stage_1_Line_List);
		((CSoldier*)temp)->InsertAttackSoldier(_T("AtkSoldier_36"));
		CObjMgr::GetInst()->GetObjList(OBJ_MONSTER)->push_back(temp);
		isWave_7_finished = true;
	}
}
