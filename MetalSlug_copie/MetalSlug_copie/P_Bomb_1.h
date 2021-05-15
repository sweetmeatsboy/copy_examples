#pragma once
#include "PlayerBullet.h"
class CAniDCSet;
class CLine;

class CP_Bomb_1 : public CPlayerBullet
{
public:
	static const RTTI m_Rtti;
protected:	//라인관련.
	CLine* m_CurLine;
	CLine* SelectedLine;
	float LineOnPosPlayerY;
	list<CLine*>* m_Line_List;
	list<CLine*>::iterator m_Line_Pos;
public:
	bool isDead;
	bool PlayerIsMyLeft;
	int m_DeltaCount;
public:	//바운딩 관련 내용.
	int m_BoundCount;	//대전차폭탄 은 3번 튕기면 터지도록.

protected:
	CAniDCSet* m_Ani;
	DWORD m_AniTimer;
	int m_CurFrame;
public:
	void SetPlayerIsMyLeft(bool _bool) { PlayerIsMyLeft = _bool; }
	void isOutOfFocus();
	void Move();
public:
	virtual void SetAngle(float _fAngle);
	virtual void CheckLineCollision();
	virtual void CheckCollision(CObj* _Something);

	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	CP_Bomb_1() {}
	virtual ~CP_Bomb_1() {}
};
