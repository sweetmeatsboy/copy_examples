#pragma once

class CCollisionMgr
{
private:
	static CCollisionMgr* inst;
	CCollisionMgr() {}
	~CCollisionMgr() {}
private:
	CObj* m_Player;
	list<CObj*>* m_List_1;
	list<CObj*>::iterator m_List_1_Iter;
	list<CObj*>* m_List_2;
	list<CObj*>::iterator m_List_2_Iter;
public:
	static CCollisionMgr* Getinst();
	static void DestroyInst();

public:
	void Progress();
	void Release();
private:
	void CheckPlayerWithEnemyBullet();
	void CheckEnemyWithPlayerBullet();
	void CheckPlayerWithEnemy();
	void CheckNomalObjWithPlayerBullet();
	void CheckPlayerWithNomalObj();

	void CheckPlayerWithItem();
	void CheckPlayerWithSlug();
	void CheckNPCWithPlayer();
};
