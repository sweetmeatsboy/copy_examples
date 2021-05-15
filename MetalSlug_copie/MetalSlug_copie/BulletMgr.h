#pragma once

#include "P_NormalBullet.h"
#include "P_Knife.h"
#include "P_H.h"
#include "P_F.h"
#include "P_S.h"
#include "P_Bomb_1.h"

#include "E_NomalBullet.h"
#include "E_Bakgeok.h"
#include "E_Mine.h"
#include "E_BallingBomb.h"
#include "E_Bomb_1.h"
#include "E_Bomb_2.h"

class CBulletMgr
{
public:
	static void Fire(float _x, float _y, float _fAngle, W_TYPE _W_Type, bool isLeft)
	{
		CObj* bullet = NULL;
		int temp = 0;
		switch (_W_Type)
		{
		case W_KNIFE:
			bullet = CObjFactory<CP_Knife>::CreateObj();
			bullet->SetPos(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET)->push_back(bullet);
			break;
		case W_NOMAL:
			bullet = CObjFactory<CP_NomalBullet>::CreateObj();
			bullet->SetPos(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET)->push_back(bullet);
			break;
		case W_H:
			bullet = CObjFactory<CP_H>::CreateObj();
			bullet->SetPos(_x, _y);
			bullet->SetAngle(_fAngle);
			((CP_H*)bullet)->SetIsLeft(isLeft);;
			CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET)->push_back(bullet);
			break;
		case W_F:
			bullet = CObjFactory<CP_F>::CreateObj();
			((CP_S*)bullet)->SetPos(_x, _y);
			((CP_S*)bullet)->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET)->push_back(bullet);
			break;
		case W_S:
			bullet = CObjFactory<CP_S>::CreateObj();
			((CP_S*)bullet)->SetPos(_x, _y + 10);
			((CP_S*)bullet)->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET)->push_back(bullet);
			break;
		case W_BOMB:
			bullet = CObjFactory<CP_Bomb_1>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET)->push_back(bullet);
			break;
		}
		bullet = NULL;
	}
	static void EnemyFire(float _x, float _y, float _fAngle, EW_TYPE _W_Type, bool isLeft)
	{
		CObj* bullet = NULL;

		switch (_W_Type)
		{
		case EW_KNIFE:
			bullet = CObjFactory<CP_Knife>::CreateObj(_x, _y);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		case EW_NOMAL:
			bullet = CObjFactory<CE_NomalBullet>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		case EW_BOMB_1:
			bullet = CObjFactory<CE_Bomb_1>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		case EW_MINE:
			bullet = CObjFactory<CE_Mine>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		case EW_BALLING_BOMB:
			bullet = CObjFactory<CE_BallingBomb>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		case EW_BAKGEOK:
			bullet = CObjFactory<CE_Bakgeok>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		case EW_BOMB_2:
			bullet = CObjFactory<CE_Bomb_2>::CreateObj(_x, _y);
			bullet->SetAngle(_fAngle);
			CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(bullet);
			break;
		}
		bullet = NULL;
	}
};