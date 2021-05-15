#pragma once

class CPlayerBullet : public CObj
{
public:
	static const RTTI m_Rtti;
protected:	//라인관련.
	CLine* m_CurLine;
	CLine* SelectedLine;
	float LineOnPosPlayerY;
	list<CLine*>* m_Line_List;
	list<CLine*>::iterator m_Line_Pos;

	virtual void CheckLineCollision() = 0;

protected:
	float Atk;
	bool isDead;
public:
	int m_DeltaCount;
	float GetAtk() const { return Atk; }
	void SetIsDead(bool _bool) { isDead = _bool; }
public:
	virtual void Initialize(void) = 0;
	virtual int Progress(void) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release(void) = 0;
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CPlayerBullet() {}
	virtual ~CPlayerBullet() {}
};