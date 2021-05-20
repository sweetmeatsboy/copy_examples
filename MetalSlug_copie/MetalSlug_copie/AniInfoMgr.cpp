#include "stdafx.h"

CAniInfoMgr* CAniInfoMgr::inst = nullptr;
CAniInfoMgr* CAniInfoMgr::Getinst()
{
	if (inst == nullptr)
		inst = new CAniInfoMgr();
	return inst;
}

void CAniInfoMgr::DestroyInst()
{
	Getinst()->Release();
	if (inst != nullptr)
		delete inst;
	inst = nullptr;
}

void CAniInfoMgr::Release()
{

	m_AniSetDCList.clear();
	m_FrameList.clear();

	map<wstring, CAniDCSet*>::iterator AniList_1_Iter;
	for (AniList_1_Iter = m_Player_1_AniSet.begin();
		AniList_1_Iter != m_Player_1_AniSet.end(); ++AniList_1_Iter)
	{
		delete (*AniList_1_Iter).second;
		(*AniList_1_Iter).second = NULL;
	}
	for (AniList_1_Iter = m_Player_Weapon_AniSet.begin();
		AniList_1_Iter != m_Player_Weapon_AniSet.end(); ++AniList_1_Iter)
	{
		delete (*AniList_1_Iter).second;
		(*AniList_1_Iter).second = NULL;
	}
	for (AniList_1_Iter = m_Nomal_Soldier_AniSet.begin();
		AniList_1_Iter != m_Nomal_Soldier_AniSet.end(); ++AniList_1_Iter)
	{
		delete (*AniList_1_Iter).second;
		(*AniList_1_Iter).second = NULL;
	}
	for (AniList_1_Iter = m_ETC_Item_AniSet.begin();
		AniList_1_Iter != m_ETC_Item_AniSet.end(); ++AniList_1_Iter)
	{
		delete (*AniList_1_Iter).second;
		(*AniList_1_Iter).second = NULL;
	}
	m_Player_1_AniSet.clear();
	m_Player_Weapon_AniSet.clear();
	m_Nomal_Soldier_AniSet.clear();
	m_ETC_Item_AniSet.clear();
}

void CAniInfoMgr::SetAniDCSetMap(AniDCSetMap& _map, int _idx, const TCHAR* _name)
{
	_map[_name] = m_AniSetDCList[_idx];
	_map[_name]->SetAniName(_name);
}
void CAniInfoMgr::LoadAniInfo_Boss_1()
{
	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/Boss_1.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Boss_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_Boss_1");
	
	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("AniDCSet_GetFrameInfoByIdx"), _T("Error"), Boss_Atlas == nullptr);
	if (pop)
		return;

	//우선 프레임을 얻어온다.
	int sceneCnt = temp->m_vScenes.size();
	int aniCnt = temp->m_vAnimates.size();
	for (int i = 0; i < sceneCnt; i++)
	{
		auto scene = temp->m_vScenes.at(i);
		auto *frame = new CFrameDC(scene->m_rcMain,scene->m_ptMain
			,temp->m_dwBackColor);
		m_FrameList[i] = frame;
	}
	for (int n = 0; n < aniCnt; ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		int cutCnt = temp->m_vAnimates.at(n)->getCntScene();
		for (int y = 0; y < cutCnt; ++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		tempAni->SetAtlasMapName("Atals_Boss_1");
		tempAni->SetScale(2.5f, 2.5f);
	}

	SetAniDCSetMap(m_Boss_1_AniSet, 0, _T("BIG_CANON_APPERENCE"));
	SetAniDCSetMap(m_Boss_1_AniSet,1, _T("BIG_CANON_TARGETTING"));
	SetAniDCSetMap(m_Boss_1_AniSet,2, _T("BIG_CANON_ANGLE_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,3, _T("BIG_CANON_ANGLE_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,4, _T("BIG_CANON_ANGLE_3"));
	SetAniDCSetMap(m_Boss_1_AniSet,5, _T("BIG_CANON_ANGLE_4"));
	SetAniDCSetMap(m_Boss_1_AniSet,6, _T("BIG_CANON_ANGLE_5"));
	SetAniDCSetMap(m_Boss_1_AniSet,7, _T("BIG_CANON_BULLET_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,8, _T("BIG_CANON_BULLET_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,48, _T("BIG_CANON_BULLET_3"));
	SetAniDCSetMap(m_Boss_1_AniSet,9, _T("BIG_CANON_BULLET_4"));
	SetAniDCSetMap(m_Boss_1_AniSet,10, _T("BIG_CANON_BOMB_SHELL_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,11, _T("BIG_CANON_BOMB_SHELL_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,12, _T("BIG_CANON_SFX_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,13, _T("BIG_CANON_SFX_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,14, _T("SIDE_TURRET_1_IDLE"));
	SetAniDCSetMap(m_Boss_1_AniSet,15, _T("SIDE_TURRET_2_IDLE"));
	SetAniDCSetMap(m_Boss_1_AniSet,16, _T("SIDE_TURRET_3_IDLE"));
	SetAniDCSetMap(m_Boss_1_AniSet,17, _T("SIDE_ONE_TURRET_1_IDLE"));
	SetAniDCSetMap(m_Boss_1_AniSet,45, _T("SIDE_ONE_TURRET_2_IDLE"));
	SetAniDCSetMap(m_Boss_1_AniSet,46, _T("SIDE_ONE_TURRET_3_IDLE"));
	SetAniDCSetMap(m_Boss_1_AniSet,18, _T("SIDE_TURRET_TURNING"));
	SetAniDCSetMap(m_Boss_1_AniSet,19, _T("SIDE_ONE_TURRET_TURNING"));
	SetAniDCSetMap(m_Boss_1_AniSet,20, _T("SIDE_TURRET_FIRING_LEFT"));
	SetAniDCSetMap(m_Boss_1_AniSet,47, _T("SIDE_TURRET_FIRING_MID"));
	SetAniDCSetMap(m_Boss_1_AniSet,21, _T("SIDE_TURRET_FIRING_RIGHT"));
	SetAniDCSetMap(m_Boss_1_AniSet,22, _T("SIDE_ONE_TURRET_FIRING_MID"));
	SetAniDCSetMap(m_Boss_1_AniSet,23, _T("SIDE_ONE_TURRET_FIRING_LEFT"));
	SetAniDCSetMap(m_Boss_1_AniSet,24, _T("SIDE_ONE_TURRET_FIRING_RIGHT"));
	SetAniDCSetMap(m_Boss_1_AniSet,25, _T("SIDE_TURRET_FIRING_SFX_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,26, _T("SIDE_TURRET_FIRING_SFX_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,27, _T("SIDE_TURRET_FIRING_SFX_3"));
	SetAniDCSetMap(m_Boss_1_AniSet,28, _T("SIDE_ONE_TURRET_FIRING_SFX_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,29, _T("SIDE_ONE_TURRET_FIRING_SFX_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,30, _T("SIDE_ONE_TURRET_FIRING_SFX_3"));
	SetAniDCSetMap(m_Boss_1_AniSet,31, _T("BODY_PARTS"));
	SetAniDCSetMap(m_Boss_1_AniSet,32, _T("WHELE_PARTS_FRONT"));
	SetAniDCSetMap(m_Boss_1_AniSet,33, _T("WHELE_PARTS_BACK"));
	SetAniDCSetMap(m_Boss_1_AniSet,34, _T("BROKEN_BODY_PARTS"));
	SetAniDCSetMap(m_Boss_1_AniSet,35, _T("RADAR_PARTS_1"));
	SetAniDCSetMap(m_Boss_1_AniSet,36, _T("RADAR_PARTS_2"));
	SetAniDCSetMap(m_Boss_1_AniSet,37, _T("RADAR_PARTS_3"));
	SetAniDCSetMap(m_Boss_1_AniSet,38, _T("ICON_PARTS"));
	SetAniDCSetMap(m_Boss_1_AniSet,39, _T("ICON_PARTS_SFX"));
	SetAniDCSetMap(m_Boss_1_AniSet,40, _T("SHIP_OPEN_SFX"));
	SetAniDCSetMap(m_Boss_1_AniSet,41, _T("DEAD_BOSS"));
	SetAniDCSetMap(m_Boss_1_AniSet,42, _T("SIDE_TURRET_FIRING_SFX_0"));
	SetAniDCSetMap(m_Boss_1_AniSet,43, _T("SIDE_ONE_TURRET_FIRING_SFX_0"));
	SetAniDCSetMap(m_Boss_1_AniSet,44, _T("SIDE_TURRET_BULLET"));
	if (temp != NULL)
		delete temp;
	temp = NULL;
}

void CAniInfoMgr::LoadAniInfo_ETC_Effect()
{
	//추후 아이템 파일을 다시 다른걸로 따거나 해서 문제를 해결할 것,.
	//일단은 리소스 매니져에서 해당 함수를 주석처리 해둠.

	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/Effect_Explosiom.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_ECT_Effect");
	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("AniDCSet_GetFrameInfoByIdx"), _T("Error"), Player_Weapon_Atlas == nullptr);
	if (pop)
		return;

	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		m_AniSetDCList[n]->SetAtlasMapName("Atals_ECT_Effect");
		m_AniSetDCList[n]->SetScale(2.f, 2.f);
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.

	SetAniDCSetMap(m_ETC_Effect_AniSet,0, _T("Explosion_Nomal"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,1, _T("Explosion_Middle"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,2, _T("Explosion_Max"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,3, _T("Explosion_Bomb"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,4, _T("Explosion_Bomb_Max"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,5, _T("Explosion_Mine"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,6, _T("Explosion_Mine_2"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,7, _T("Explosion_BallingBomb"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,8, _T("Explosion_FireBomb"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,10, _T("Explosion_FireBomb_Max"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,11, _T("Explosion_FireBomb_Finished"));
	SetAniDCSetMap(m_ETC_Effect_AniSet,15, _T("Explosion_Huge"));

	if (temp != NULL)
		delete temp;
	temp = NULL;
}


void CAniInfoMgr::LoadAniInfo_EnemyWeapon()
{
	//추후 아이템 파일을 다시 다른걸로 따거나 해서 문제를 해결할 것,.
	//일단은 리소스 매니져에서 해당 함수를 주석처리 해둠.

	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/E_Weapon.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_Enemy_Weapon");
	
	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("Atlas Error"), _T("Enemy_Weapon"), Player_Weapon_Atlas == nullptr);
	if (pop)
		return;

	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		m_AniSetDCList[n]->SetAtlasMapName("Atals_Enemy_Weapon");
		m_AniSetDCList[n]->SetScale(2.f, 2.f);


	
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,0, _T("EW_BOMB_1"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,1, _T("EW_BALLING_BOMB"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,2, _T("EW_MINE"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,3, _T("EW_BAKGEOK"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,5, _T("BANK_SFX"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,6, _T("EW_TANK_NOMAL_BULLET"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,7, _T("EW_BOMB_2"));
	SetAniDCSetMap(m_Enemy_Weapon_AniSet,8, _T("EW_NOMAL"));
	
	if (temp != NULL)
		delete temp;
	temp = NULL;
}


void CAniInfoMgr::LoadAniInfo_UI_Set_1()
{
	//추후 아이템 파일을 다시 다른걸로 따거나 해서 문제를 해결할 것,.
	//일단은 리소스 매니져에서 해당 함수를 주석처리 해둠.

	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/UISet_1.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_UI_Set_1");
	
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("AniInfoMgr"), _T("Atals_UI_Set_1 Load Failed"), Player_Weapon_Atlas == nullptr))
		return;

	int sceneCnt = temp->m_vScenes.size();
	int aniCnt = temp->m_vAnimates.size();
	//우선 프레임을 얻어온다.
	for (int h = 0; h < sceneCnt; ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < aniCnt; ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		auto aniFrameCnt = temp->m_vAnimates.at(n)->getCntScene();
		for (int y = 0; y < aniFrameCnt;++y)
		{
			auto tag = temp->m_vAnimates.at(n)->getIdxOfScene(y);
			auto targetFrame = m_FrameList[tag->m_dwIndex];
			tempAni->AddFrameInfo(targetFrame, tag->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		m_AniSetDCList[n]->SetAtlasMapName("Atals_UI_Set_1");
		m_AniSetDCList[n]->SetScale(2.f, 2.f);

	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.

	////우선 프레임을 얻어온다.
	//for (unsigned int h = 0;
	//	h < temp->m_vScenes.size(); ++h)
	//{
	//	m_FrameList[h] = new CFrameDC(
	//		temp->m_vScenes.at(h)->m_rcMain,
	//		temp->m_vScenes.at(h)->m_ptMain,
	//		temp->m_dwBackColor);
	//}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	//for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	//{
	//	CAniDCSet* tempAni = new CAniDCSet();
	//	for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
	//		++y)
	//	{
	//		tempAni->AddFrameInfo(
	//			m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
	//			temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
	//	}
	//	m_AniSetDCList[n] = tempAni;
	//	m_AniSetDCList[n]->SetAtlasMapName("Atals_UI_Set_1");
	//	m_AniSetDCList[n]->SetScale(2.f, 2.f);

	//}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.

	SetAniDCSetMap(m_UI_Set_1_AniSet, 0, _T("SMALL_SILVER"));
	SetAniDCSetMap(m_UI_Set_1_AniSet, 1, _T("NOMAL_SILVER"));
	SetAniDCSetMap(m_UI_Set_1_AniSet, 2, _T("BIG_SILVER"));
	SetAniDCSetMap(m_UI_Set_1_AniSet, 3, _T("BIG_GOLD"));
	SetAniDCSetMap(m_UI_Set_1_AniSet, 4, _T("SMALL_GOLD"));
	SetAniDCSetMap(m_UI_Set_1_AniSet, 5, _T("UIBOX_SET"));
	SetAniDCSetMap(m_UI_Set_1_AniSet, 6, _T("NPC_COUNT"));
	if (temp != NULL)
		delete temp;
	temp = NULL;
}



void CAniInfoMgr::LoadAniInfo_NomalOBJ_1()
{
	//추후 아이템 파일을 다시 다른걸로 따거나 해서 문제를 해결할 것,.
	//일단은 리소스 매니져에서 해당 함수를 주석처리 해둠.

	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/NomalObjectList_1.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atlas_NomalOBJ_1");
	
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("AniInfoMgr"), _T("Atlas_NomalOBJ_1 Load Failed"), Player_Weapon_Atlas == nullptr))
		return;

	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		m_AniSetDCList[n]->SetScale(2.f, 2.f);
		//2배로 늘리면 출력이 안된다 왤까/...?
		m_AniSetDCList[n]->SetAtlasMapName("Atlas_NomalOBJ_1");
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.

	SetAniDCSetMap(m_NormalObjectAniSet_1, 0, _T("PRISONER_SIT_LOCK"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 1, _T("PRISONER_SIT_FREE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 20, _T("PRISONER_HAING"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 21, _T("PRISONER_GIVE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 22, _T("PRISONER_RUN"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 2, _T("PRISONER_STAND_LOCK"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 3, _T("PRISONER_STAND_FREE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 4, _T("ITEM_BOX"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 5, _T("MESS_KIT_STATE_1"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 6, _T("MESS_KIT_STATE_2"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 7, _T("MESS_KIT_STATE_3"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 8, _T("MESS_LIT_SMOKE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 9, _T("CAMPFIRE_SOLDIER_1"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 10, _T("CAMPFIRE_SOLDIER_2"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 11, _T("SUN_MAN_1_NO_DIE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 12, _T("SUN_MAN_1_DIE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 13, _T("SUN_MAN_2_NO_DIE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 14, _T("SUN_MAN_2_DIE"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 28, _T("STAGE_1_FRONT_OBJ_1"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 29, _T("STAGE_1_FRONT_OBJ_2"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 16, _T("STAGE_1_ROCK"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 17, _T("STAGE_1_FRONT_OBJ_3"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 18, _T("STAGE_1_FRONT_DOOR_1"));
	SetAniDCSetMap(m_NormalObjectAniSet_1, 19, _T("STAGE_1_FRONT_DOOR_2"));

	if (temp != NULL)
		delete temp;
	temp = NULL;
}

void CAniInfoMgr::LoadAniInfo_ETC_Item()
{
	//추후 아이템 파일을 다시 다른걸로 따거나 해서 문제를 해결할 것,.
	//일단은 리소스 매니져에서 해당 함수를 주석처리 해둠.

	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/Item.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_ECT_Item");
	
	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("Atlas Error"), _T("Player_Weapon"), Player_Weapon_Atlas == nullptr);
	if (pop)
		return;

	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		m_AniSetDCList[n]->SetAtlasMapName("Atals_ECT_Item");
		m_AniSetDCList[n]->SetScale(2.f, 2.f);
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.

	SetAniDCSetMap(m_ETC_Item_AniSet, 0, _T("W_ITEM_RELOAD_BOMB"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 1, _T("W_ITEM_RECHARGE_OIL"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 2, _T("W_ITEM_RELOAD_BULLET"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 3, _T("W_ITEM_CHANGE_FIREBOMB"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 4, _T("W_ITEM_CHANGE_BOMB"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 5, _T("W_ITEM_RELOAD_SLUG_BOMB"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 6, _T("W_ITEM_H"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 7, _T("W_ITEM_F"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 8, _T("W_ITEM_S"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 9, _T("N_ITEM_CURE"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 10, _T("N_ITEM_FISH"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 11, _T("N_ITEM_BREAD"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 12, _T("N_ITEM_CAN"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 13, _T("N_ITEM_BANANA"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 14, _T("N_ITEM_CHICKEN"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 15, _T("N_ITEM_MANDOO"));
	SetAniDCSetMap(m_ETC_Item_AniSet, 16, _T("W_ITEM_R"));

	if (temp != NULL)
		delete temp;
	temp = NULL;
}

void CAniInfoMgr::LoadAniInfo_PlayerWeapon()
{
	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/PlayerWeapon.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_Player_Weapon");

	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("Atlas Error"), _T("Player_Weapon"), Player_Weapon_Atlas == nullptr);
	if (pop)
		return;

	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;
		m_AniSetDCList[n]->SetAtlasMapName("Atals_Player_Weapon");
		m_AniSetDCList[n]->SetScale(2.f, 2.f);
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.


	SetAniDCSetMap(m_Player_Weapon_AniSet, 0, _T("P_W_H"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 1, _T("P_W_LUNCHER"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 2, _T("P_W_LUNCHER_SMOKE"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 3, _T("P_W_DOG_SHOOT_HIGH"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 4, _T("P_W_DOG_HIGH"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 5, _T("P_W_DOG_SHOOT_UP"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 6, _T("P_W_DOG_UP"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 7, _T("P_W_DOG_SHOOT_MID"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 8, _T("P_W_DOG_MID"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 9, _T("P_W_DOG_SHOOT_UNDER"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 10, _T("P_W_DOG_UNDER"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 12, _T("P_W_F_SPLASH"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 14, _T("P_W_F_UP_SPLASH"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 16, _T("P_W_F_DOWN_SPLASH"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 17, _T("P_W_F"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 18, _T("P_W_F_DOWN"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 19, _T("P_W_F_UP"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 20, _T("P_W_S"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 23, _T("P_W_S_DOWN"));
	SetAniDCSetMap(m_Player_Weapon_AniSet, 24, _T("P_W_S_UP"));

	if (temp != NULL)
		delete temp;
	temp = NULL;
}

void CAniInfoMgr::LoadAniInfo_NomalSoldier()
{
	m_AniSetDCList.clear();
	m_FrameList.clear();
	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/Enemy_RebelSoldier.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_Weapon_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_Rebel_Nomal");
	
	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("Atlas Error"), _T("ExtraSoldier"), Player_Weapon_Atlas == nullptr);
	if (pop)
		return;
	
	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;

		m_AniSetDCList[n]->SetAtlasMapName("Atals_Rebel_Nomal");
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.

	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 4, _T("Extra_4"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 9, _T("Extra_9"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 10, _T("Extra_10"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 104, _T("Extra_104"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 17, _T("Extra_17"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 11, _T("Extra_11"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 12, _T("Extra_12"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 13, _T("Extra_13"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 51, _T("Extra_51"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 74, _T("Extra_74"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 75, _T("Extra_75"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 18, _T("Extra_18"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 19, _T("Extra_19"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 84, _T("Extra_84"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 14, _T("Reaction_14"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 15, _T("Reaction_15"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 28, _T("DeadSoldier_28"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 52, _T("DeadSoldier_52"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 53, _T("DeadSoldier_53"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 54, _T("DeadSoldier_54"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 55, _T("DeadSoldier_55"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 56, _T("DeadSoldier_56"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 57, _T("DeadSoldier_57"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 58, _T("DeadSoldier_58"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 59, _T("DeadSoldier_59"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 60, _T("DeadSoldier_60"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 67, _T("DeadSoldier_67"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 68, _T("DeadSoldier_68"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 69, _T("DeadSoldier_69"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 70, _T("DeadSoldier_70"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 71, _T("DeadSoldier_71"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 72, _T("DeadSoldier_72"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 100, _T("DeadSoldier_100"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 102, _T("DeadSoldier_102"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 103, _T("DeadSoldier_103"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 29, _T("AtkSoldier_29"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 30, _T("AtkSoldier_30"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 32, _T("AtkSoldier_32"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 33, _T("AtkSoldier_33"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 34, _T("AtkSoldier_34"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 35, _T("AtkSoldier_35"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 36, _T("AtkSoldier_36"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 38, _T("AtkSoldier_38"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 40, _T("AtkSoldier_40"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 41, _T("AtkSoldier_41"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 42, _T("AtkSoldier_42"));
	SetAniDCSetMap(m_Nomal_Soldier_AniSet, 77, _T("AtkSoldier_77"));

	if (temp != NULL)
		delete temp;
	temp = NULL;
}
void CAniInfoMgr::LoadAniInfo_Player_1()
{
	m_AniSetDCList.clear();
	m_FrameList.clear();

	CSprite* temp = new CSprite();
	//Player_1 작업 시작.
	//Player_1 Animation Info로드.
	temp->LoadData(_T("../SpriteInfo/Player_1.spt"));
	//아틀라스맵 소환!
	CBitmapDC* Player_1_Atlas = CResourceMgr::GetInst()->GetBitDCMap("Atals_Player_1");

	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("Atlas Error"), _T("Player_1"), Player_1_Atlas == nullptr);
	if (pop)
		return;
	
	//우선 프레임을 얻어온다.
	for (unsigned int h = 0;
		h < temp->m_vScenes.size(); ++h)
	{
		m_FrameList[h] = new CFrameDC(
			temp->m_vScenes.at(h)->m_rcMain,
			temp->m_vScenes.at(h)->m_ptMain,
			temp->m_dwBackColor);
	}	//이렇게 하면 툴에서 따온 인덱스 번호대로 맵에 HDC들이 저장될것이다.

	for (unsigned int n = 0; n < temp->m_vAnimates.size(); ++n)
	{
		CAniDCSet* tempAni = new CAniDCSet();
		for (unsigned int y = 0; y < temp->m_vAnimates.at(n)->getCntScene();
			++y)
		{
			tempAni->AddFrameInfo(
				m_FrameList[temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwIndex],
				temp->m_vAnimates.at(n)->getIdxOfScene(y)->m_dwOutputTime);
		}
		m_AniSetDCList[n] = tempAni;

		m_AniSetDCList[n]->SetAtlasMapName("Atals_Player_1");
	}	//모든 애니메이트들의 안에 있는 인덱스들을 모조리 저장한다.
	//일반 상태 및 딱총일떄의 애니메이션 관련 사항들.///////////

	SetAniDCSetMap(m_Player_1_AniSet, 0, _T("BODY_IDLE"));
	SetAniDCSetMap(m_Player_1_AniSet, 1, _T("BODY_RUN"));
	SetAniDCSetMap(m_Player_1_AniSet, 2, _T("LEG_IDLE"));
	SetAniDCSetMap(m_Player_1_AniSet, 3, _T("LEG_RUN"));
	SetAniDCSetMap(m_Player_1_AniSet, 4, _T("LEG_JUMP"));
	SetAniDCSetMap(m_Player_1_AniSet, 5, _T("LEG_DIR_JUMP"));
	SetAniDCSetMap(m_Player_1_AniSet, 6, _T("BODY_SHOOT_NOMAL"));
	SetAniDCSetMap(m_Player_1_AniSet, 7, _T("BODY_LOOK_NOMAL_UP"));
	SetAniDCSetMap(m_Player_1_AniSet, 8, _T("BODY_SHOOT_NOMAL_UP"));
	SetAniDCSetMap(m_Player_1_AniSet, 9, _T("BODY_LOOK_NOMAL_DOWN"));
	SetAniDCSetMap(m_Player_1_AniSet, 10, _T("BODY_SHOOT_NOMAL_DOWN"));
	SetAniDCSetMap(m_Player_1_AniSet, 11, _T("BODY_SHOOT_KNIFE"));
	SetAniDCSetMap(m_Player_1_AniSet, 12, _T("BODY_SHOOT_BOMB"));
	SetAniDCSetMap(m_Player_1_AniSet, 13, _T("BODY_JUMP"));
	SetAniDCSetMap(m_Player_1_AniSet, 14, _T("BODY_DIR_JUMP"));
	SetAniDCSetMap(m_Player_1_AniSet, 15, _T("BODY_WEAPON_IDLE"));
	SetAniDCSetMap(m_Player_1_AniSet, 16, _T("BODY_WEAPON_RUN"));
	SetAniDCSetMap(m_Player_1_AniSet, 17, _T("BODY_SHOOT_WEAPON_UP"));
	SetAniDCSetMap(m_Player_1_AniSet, 18, _T("BODY_SHOOT_WEAPON_RIGHT_TO_UP"));
	SetAniDCSetMap(m_Player_1_AniSet, 19, _T("BODY_SHOOT_WEAPON_DOWN"));
	SetAniDCSetMap(m_Player_1_AniSet, 20, _T("BODY_WEAPON_JUMP"));
	SetAniDCSetMap(m_Player_1_AniSet, 21, _T("BODY_WEAPON_DIR_JUMP"));
	SetAniDCSetMap(m_Player_1_AniSet, 22, _T("BODY_SHOOT_WEAPON"));
	SetAniDCSetMap(m_Player_1_AniSet, 23, _T("BODY_SHOOT_WEAPON_RIGHT_TO_DOWN"));
	SetAniDCSetMap(m_Player_1_AniSet, 24, _T("BODY_LOOK_WEAPON_UP"));
	SetAniDCSetMap(m_Player_1_AniSet, 25, _T("BODY_LOOK_WEAPON_DOWN"));
	SetAniDCSetMap(m_Player_1_AniSet, 26, _T("BODY_SHOOT_WEAPON_DOWN_TO_RIGHT"));
	SetAniDCSetMap(m_Player_1_AniSet, 27, _T("BODY_SHOOT_WEAPON_UP_TO_RIGHT"));
	
	SetAniDCSetMap(m_Player_1_AniSet, 28, _T("SIT_TRANSLATE"));
	SetAniDCSetMap(m_Player_1_AniSet, 29, _T("SIT_IDLE"));
	SetAniDCSetMap(m_Player_1_AniSet, 30, _T("SIT_SHOOT_NOMAL"));
	SetAniDCSetMap(m_Player_1_AniSet, 31, _T("SIT_SHOOT_KNIFE"));
	SetAniDCSetMap(m_Player_1_AniSet, 32, _T("SIT_SHOOT_BOMB"));
	SetAniDCSetMap(m_Player_1_AniSet, 33, _T("IN_TO_SLUG"));
	SetAniDCSetMap(m_Player_1_AniSet, 34, _T("PLAYER_1_APPEARANCE"));

	SetAniDCSetMap(m_Player_1_AniSet, 35, _T("PLAYER_1_DEAD_LAND"));
	SetAniDCSetMap(m_Player_1_AniSet, 36, _T("PLAYER_1_DEAD_JUMPING"));
	SetAniDCSetMap(m_Player_1_AniSet, 37, _T("PLAYER_1_DEAD_FIRE"));

	////////////////////////////////////////////////////////
	if (temp != NULL)
		delete temp;
	temp = NULL;
}

CAniDCSet* CAniInfoMgr::GetAniDCSet(const _TCHAR* _setName, const TCHAR* _name)
{
	auto pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("AniSetMap Not Exist"), _name, aniSetMap.find(_setName) == aniSetMap.end());
	if (pop)
		return nullptr;

	AniDCSetMap& _aniSet = *aniSetMap[_setName];
	pop = ErrorMgr::GetInst().ErrBoxPopupT(_T("AniDCSet Not Exist"), _name, _aniSet[_name] == nullptr);
	if (pop)
		return nullptr;
	return _aniSet[_name];
}

void CAniInfoMgr::LoadResource_Animation()
{
	CAniInfoMgr::Getinst()->LoadAniInfo_Player_1();	//플레이어 1의 애니메이션 로드.
	CAniInfoMgr::Getinst()->LoadAniInfo_PlayerWeapon();	//플레이어의 무기 애니메이션 로드.

	CAniInfoMgr::Getinst()->LoadAniInfo_NomalSoldier();
	CAniInfoMgr::Getinst()->LoadAniInfo_UI_Set_1();
	CAniInfoMgr::Getinst()->LoadAniInfo_Boss_1();
	CAniInfoMgr::Getinst()->LoadAniInfo_EnemyWeapon();
	CAniInfoMgr::Getinst()->LoadAniInfo_NomalOBJ_1();

	CAniInfoMgr::Getinst()->LoadAniInfo_ETC_Item();
	CAniInfoMgr::Getinst()->LoadAniInfo_ETC_Effect();
}
