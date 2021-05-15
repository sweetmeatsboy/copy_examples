#pragma once
#include "PlayerBullet.h"
class CLine;
class CBitmapDC;

class CP_NomalBullet : public CPlayerBullet
{
public:
	static const RTTI m_Rtti;

protected:
	CLine* m_CurLine;
	CLine* SelectedLine;
	float LineOnPosPlayerY;
	list<CLine*>* m_Line_List;
	list<CLine*>::iterator m_Line_Pos;
protected:
	bool isDead;
public:
	bool isLeft;
	int m_DeltaCount;
	CBitmapDC* m_Img_1;
	CBitmapDC* m_Img_2;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void CheckCollision(CObj* _Something);
	virtual void CheckLineCollision();
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CP_NomalBullet() {}
	virtual ~CP_NomalBullet() {}
};