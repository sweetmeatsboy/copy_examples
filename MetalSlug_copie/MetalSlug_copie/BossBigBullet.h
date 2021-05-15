#pragma once

class CBossBigBullet : public CObj
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
public:	//바운딩 관련 내용.
	void SetAniName(const TCHAR* _Name);	//애니메이션 설정용.

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
	CBossBigBullet() {}
	virtual ~CBossBigBullet() {}
};