#pragma once

class CDoor : public CNormalObj
{
public:
	static const RTTI m_Rtti;
private:
	float MovingDistance;
	float temp;
	float HP;	//총알에 일정횟수 이상 맞을 때 열리도록.
private:
	CAniDCSet* m_Ani;
	bool isDead;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
};