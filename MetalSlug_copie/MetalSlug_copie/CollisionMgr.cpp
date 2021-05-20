#include "stdafx.h"


CCollisionMgr* CCollisionMgr::inst = NULL;

CCollisionMgr* CCollisionMgr::Getinst()
{
	if (inst == NULL)
	{
		inst = new CCollisionMgr();
		inst->m_Player = NULL;
		inst->m_List_1 = NULL;
		inst->m_List_2 = NULL;
	}
	return inst;
}

void CCollisionMgr::DestroyInst()
{
	if (inst != NULL)
	{
		inst->Release();
		delete inst;
	}
	inst = NULL;
}

void CCollisionMgr::Progress()
{
	auto no_err = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->empty() == false;
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("CollisionMgr's progress"), _T("Player 미지정 오류"), no_err == false))
		return;

	Getinst()->m_Player = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();
	CheckPlayerWithEnemyBullet();
	CheckPlayerWithEnemy();
	CheckPlayerWithItem();
	CheckPlayerWithSlug();
	CheckEnemyWithPlayerBullet();
	CheckNPCWithPlayer();
	CheckPlayerWithNomalObj();
	CheckNomalObjWithPlayerBullet();
	return;
}
void CCollisionMgr::Release()
{
	m_Player = NULL;
	m_List_1 = NULL;
	m_List_2 = NULL;
}
void CCollisionMgr::CheckPlayerWithNomalObj()
{
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_OBJECT);
	RECT tempRect;
	for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
		Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
	{
		if (IntersectRect(&tempRect, &(m_Player->GetRect()), &((*m_List_2_Iter)->GetRect())))
		{
			Getinst()->m_Player->CheckCollision((*Getinst()->m_List_2_Iter));
		}
	}
}
void CCollisionMgr::CheckNomalObjWithPlayerBullet()
{
	Getinst()->m_List_1 = CObjMgr::GetInst()->GetObjList(OBJ_OBJECT);
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET);
	RECT tempRect;
	for (Getinst()->m_List_1_Iter = Getinst()->m_List_1->begin();
		Getinst()->m_List_1_Iter != Getinst()->m_List_1->end(); ++Getinst()->m_List_1_Iter)
	{
		for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
			Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
		{
			if (IntersectRect(&tempRect, &((*Getinst()->m_List_1_Iter)->GetRect()), &((*Getinst()->m_List_2_Iter)->GetRect())))
			{
				(*Getinst()->m_List_1_Iter)->CheckCollision((*Getinst()->m_List_2_Iter));
				//(*Getinst()->m_List_2_Iter)->CheckCollision( (*Getinst()->m_List_1_Iter) );
			}
		}
	}
}
void CCollisionMgr::CheckPlayerWithEnemyBullet()
{
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET);
	RECT tempRect;
	for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
		Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
	{
		if (IntersectRect(&tempRect, &(m_Player->GetRect()), &((*m_List_2_Iter)->GetRect())))
		{
			Getinst()->m_Player->CheckCollision((*Getinst()->m_List_2_Iter));
			(*Getinst()->m_List_2_Iter)->CheckCollision(Getinst()->m_Player);
		}
	}
}
void CCollisionMgr::CheckEnemyWithPlayerBullet()
{
	Getinst()->m_List_1 = CObjMgr::GetInst()->GetObjList(OBJ_MONSTER);
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_P_BULLET);
	RECT tempRect;
	for (Getinst()->m_List_1_Iter = Getinst()->m_List_1->begin();
		Getinst()->m_List_1_Iter != Getinst()->m_List_1->end(); ++Getinst()->m_List_1_Iter)
	{
		for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
			Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
		{
			if (IntersectRect(&tempRect, &((*Getinst()->m_List_1_Iter)->GetRect()), &((*Getinst()->m_List_2_Iter)->GetRect())))
			{
				(*Getinst()->m_List_1_Iter)->CheckCollision((*Getinst()->m_List_2_Iter));
				(*Getinst()->m_List_2_Iter)->CheckCollision((*Getinst()->m_List_1_Iter));
			}
		}
	}
}
void CCollisionMgr::CheckPlayerWithEnemy()
{
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_MONSTER);
	RECT tempRect;
	for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
		Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
	{
		if (IntersectRect(&tempRect, &(Getinst()->m_Player->GetRect()), &((*Getinst()->m_List_2_Iter)->GetRect())))
		{
			Getinst()->m_Player->CheckCollision((*Getinst()->m_List_2_Iter));
			(*Getinst()->m_List_2_Iter)->CheckCollision(Getinst()->m_Player);
		}
	}
}

void CCollisionMgr::CheckPlayerWithItem()
{
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_ITEM);
	RECT tempRect;
	for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
		Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
	{
		if (IntersectRect(&tempRect, &(Getinst()->m_Player->GetRect()), &((*Getinst()->m_List_2_Iter)->GetRect())))
		{
			Getinst()->m_Player->CheckCollision((*Getinst()->m_List_2_Iter));
			(*Getinst()->m_List_2_Iter)->CheckCollision(Getinst()->m_Player);
		}
	}
}
void CCollisionMgr::CheckPlayerWithSlug()
{
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_SLUG);
	RECT tempRect;
	for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
		Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
	{
		if (IntersectRect(&tempRect, &(Getinst()->m_Player->GetRect()), &((*Getinst()->m_List_2_Iter)->GetRect())))
		{
			Getinst()->m_Player->CheckCollision((*Getinst()->m_List_2_Iter));
			(*Getinst()->m_List_2_Iter)->CheckCollision(Getinst()->m_Player);
		}
	}

}
void CCollisionMgr::CheckNPCWithPlayer()
{
	Getinst()->m_List_2 = CObjMgr::GetInst()->GetObjList(OBJ_NPC);
	RECT tempRect;
	for (Getinst()->m_List_2_Iter = Getinst()->m_List_2->begin();
		Getinst()->m_List_2_Iter != Getinst()->m_List_2->end(); ++Getinst()->m_List_2_Iter)
	{
		if (IntersectRect(&tempRect, &(Getinst()->m_Player->GetRect()), &((*Getinst()->m_List_2_Iter)->GetRect())))
		{
			Getinst()->m_Player->CheckCollision((*Getinst()->m_List_2_Iter));
			(*Getinst()->m_List_2_Iter)->CheckCollision(Getinst()->m_Player);
		}
	}

}