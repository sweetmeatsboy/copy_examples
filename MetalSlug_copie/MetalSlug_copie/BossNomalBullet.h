#pragma once

class CBossNomalBullet : public CObj
{
public:
	static const RTTI m_Rtti;
protected:	//���ΰ���.
	CLine* m_CurLine;
	CLine* SelectedLine;
	float LineOnPosPlayerY;
	list<CLine*>* m_Line_List;
	list<CLine*>::iterator m_Line_Pos;
public:
	bool isDead;
	bool PlayerIsMyLeft;
public:	//�ٿ�� ���� ����.
	int m_BulletImgType;	//�� ���� ���ؼ� ź�� ũ�Ⱑ ��������.
	void SetBulletType(int _num);
	int FrameNumArr[3];
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
	CBossNomalBullet() {}
	virtual ~CBossNomalBullet() {}
};