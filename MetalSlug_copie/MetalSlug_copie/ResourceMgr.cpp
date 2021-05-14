#include "stdafx.h"

CResourceMgr* CResourceMgr::inst = nullptr;

void CResourceMgr::SetBitMap(const char* _key, const TCHAR* _path)
{
	GetInst()->m_BitDCMap[_key] = new CBitmapDC(_path);
}

void CResourceMgr::LoadResource_Intro()
{
	SetBitMap("IntroBackBuffer", _T("../Texture/SceneImg/Intro.bmp"));
	SetBitMap("IntroBackGround", _T("../Texture/SceneImg/Intro.bmp"));
}
void CResourceMgr::LoadResource_Stage_1()

{
	SetBitMap("Stage_1_BackBuffer", _T("../Texture/BackGround/BackGround_stage_1.bmp"));
	SetBitMap("Stage_1_BackGround", _T("../Texture/BackGround/BackGround_stage_1.bmp"));
}
void CResourceMgr::LoadResource_Stage_2()
{
	SetBitMap("Stage_2_BackBuffer", _T("../Texture/BackGround/BackGround_stage_2.bmp"));
	SetBitMap("Stage_2_BackGround", _T("../Texture/BackGround/BackGround_stage_2.bmp"));
	SetBitMap("Stage_2_FrontGround", _T("../Texture/BackGround/Stage_2_Front.bmp"));
}
void CResourceMgr::LoadResource_Bullet()
{
	SetBitMap("TtackChong_1", _T("../Texture/Item/TtackChong_1.bmp"));
	SetBitMap("TtackChong_2", _T("../Texture/Item/TtackChong_2.bmp"));
}

void CResourceMgr::LoadResource_AtlasMap()
{
	SetBitMap("Atals_Player_1", _T("../Texture/Player/Player_1.bmp"));
	SetBitMap("Atals_Player_2", _T("../Texture/Player/Player_2.bmp"));
	SetBitMap("Atals_Player_3", _T("../Texture/Player/Player_3.bmp"));
	SetBitMap("Atals_Player_4", _T("../Texture/Player/Player_4.bmp"));
	SetBitMap("Atals_Player_Weapon", _T("../Texture/Item/ECT_Weapon SFX_Custom.bmp"));
	SetBitMap("Atals_Enemy_Weapon", _T("../Texture/Enemy/E_Weapon_SFX.bmp"));
	SetBitMap("Atals_Slug_Tank", _T("../Texture/Slug/Slug_Tank.bmp"));
	SetBitMap("Atals_Moden_Bazuca", _T("../Texture/Enemy/Enemy_RebelSoldier(Bazooka).bmp"));
	SetBitMap("Atals_Rebel_Rifle", _T("../Texture/Enemy/Enemy_RebelSoldier(Rifle).bmp"));
	SetBitMap("Atals_Rebel_Nomal", _T("../Texture/Enemy/Enemy_RebelSoldier.bmp"));
	SetBitMap("Atals_Rebel_O'Neill", _T("../Texture/BossEnemy/Enemy_AllenO'Neill.bmp"));
	SetBitMap("Atals_ECT_Item", _T("../Texture/Item/ECT_Item.bmp"));
	SetBitMap("Atals_ECT_Effect", _T("../Texture/Item/ECT_Explosion SFX.bmp"));
	SetBitMap("Atals_UI_Set_1", _T("../Texture/UI/UI_Set_1.bmp"));
	SetBitMap("Atals_Boss_1", _T("../Texture/BossEnemy/Boss_1.bmp"));
	SetBitMap("Atlas_NomalOBJ_1", _T("../Texture/Item/ObjectList_1.bmp"));
}

void CResourceMgr::ReleaseAllResource()
{
	//todo : 리소스들 해제할 것.
}
CBitmapDC* CResourceMgr::GetBitDCMap(string _str)
{
	if (GetInst()->m_BitDCMap[_str])
		return GetInst()->m_BitDCMap[_str];
	else
	{
		MessageBox(g_hWnd, _T("해당 이름의 BitDCMap이 존재하지 않습니다."), _str.data, MB_OK);
		return NULL;
	}
}