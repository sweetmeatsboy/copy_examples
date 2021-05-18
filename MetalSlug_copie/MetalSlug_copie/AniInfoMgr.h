#pragma once

class CFrameDC;
class CAniDCSet;


class CAniInfoMgr
{
	typedef map<wstring, CAniDCSet*> AniDCSetMap;
private:
	map<wstring, AniDCSetMap*> aniSetMap;
	AniDCSetMap m_Enemy_Weapon_AniSet;
	AniDCSetMap m_Player_1_AniSet;
	AniDCSetMap m_Player_Weapon_AniSet;
	AniDCSetMap m_Nomal_Soldier_AniSet;
	AniDCSetMap m_ETC_Item_AniSet;
	AniDCSetMap m_ETC_Effect_AniSet;
	AniDCSetMap m_UI_Set_1_AniSet;

	AniDCSetMap m_NormalObjectAniSet_1;

	AniDCSetMap m_Boss_1_AniSet;

	map<int, CAniDCSet*> m_AniSetDCList;
	map<int, CFrameDC*> m_FrameList;
private:
	static CAniInfoMgr* inst;
	CAniInfoMgr() {
		aniSetMap[_T("m_Enemy_Weapon_AniSet")] = &m_Enemy_Weapon_AniSet;
		aniSetMap[_T("m_Player_1_AniSet")] = &m_Player_1_AniSet;
		aniSetMap[_T("m_Player_Weapon_AniSet")] = &m_Player_Weapon_AniSet;
		aniSetMap[_T("m_Nomal_Soldier_AniSet")] = &m_Nomal_Soldier_AniSet;
		aniSetMap[_T("m_ETC_Item_AniSet")] = &m_ETC_Item_AniSet;
		aniSetMap[_T("m_ETC_Effect_AniSet")] = &m_ETC_Effect_AniSet;
		aniSetMap[_T("m_UI_Set_1_AniSet")] = &m_UI_Set_1_AniSet;
		aniSetMap[_T("m_NormalObjectAniSet_1")] = &m_NormalObjectAniSet_1;
		aniSetMap[_T("m_Boss_1_AniSet")] = &m_Boss_1_AniSet;
	}
	~CAniInfoMgr() {}
private :
	void SetAniDCSetMap(AniDCSetMap& _map, int _idx, const TCHAR* _name);

public:
	static CAniInfoMgr* Getinst();
	static void DestroyInst();
public:
	void Release();
public:
	void LoadResource_Animation();

	void LoadAniInfo_Player_1();
	void LoadAniInfo_PlayerWeapon();
	void LoadAniInfo_EnemyWeapon();
	void LoadAniInfo_NomalSoldier();
	void LoadAniInfo_ETC_Item();
	void LoadAniInfo_ETC_Effect();
	void LoadAniInfo_UI_Set_1();
	void LoadAniInfo_NomalOBJ_1();
	void LoadAniInfo_Boss_1();

	CAniDCSet* GetAniDCSet(const _TCHAR* _setName, const TCHAR* _name);
/*
	CAniDCSet* Getplayer_1_AniSet(const TCHAR* _name);
	CAniDCSet* GetEnemy_Weapon_AniSet(const TCHAR* _name);
	CAniDCSet* GetPlayer_Weapon_AniSet(const TCHAR* _name);
	CAniDCSet* GetNormal_Soldier_AniSet(const TCHAR* _name);
	CAniDCSet* Get_ETC_Item_AniSet(const TCHAR* _name);
	CAniDCSet* Get_UI_SET_1_AniSet(const TCHAR* _Name);
	CAniDCSet* Get_ETC_Effect_AniSet(const TCHAR* _name);
	CAniDCSet* Get_Boss_1_AniSet(const TCHAR* _name);
	CAniDCSet* Get_Nomal_OBJ_1_AniSet(const TCHAR* _name);*/
};