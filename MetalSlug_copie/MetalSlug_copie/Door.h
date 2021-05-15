#pragma once

class CDoor : public CNormalObj
{
public:
	static const RTTI m_Rtti;
private:
	float MovingDistance;
	float temp;
	float HP;	//�Ѿ˿� ����Ƚ�� �̻� ���� �� ��������.
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