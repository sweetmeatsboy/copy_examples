#pragma once

class CW_Item;
class CN_Item;
class CSoldier : public CCharacter
{
public:
	static const RTTI m_Rtti;
protected:
	CObj* m_Target;	//Player�� �����Ѵ�.
	DWORD m_Atk_Delay;	//���� ������ ����.
	bool PlayerIsMyLeft;	//�÷��̾ �� ���ʿ� �ִ°�?

	bool isDead;
	CLine* SelectedLine;
	float LineOnPosPlayerY;
	list<CSoldier*> m_Patern;
	char TestStr[128];
public:
	bool isChildDead;

private:
	CW_Item* m_W_Item;
	CN_Item* m_N_Item;
public:
	virtual void LineCollision();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

	void SetTarget(CObj* _Target);

	void InsertAttackSoldier(const TCHAR* _Name);
	void InsertExtraSoldier(const TCHAR* _Name);
	void InsertReactionSoldier(const TCHAR* _Name);
	void InsertDeadSoldier(const TCHAR* _Name);

	void ClearPaternSoldier();
public:
	virtual void InsertWeaonItem(const TCHAR* _Name);	//��ü ���� �� �������� ���ϰ� ��.
	virtual void InsertNomalItem(const TCHAR* _Item);	//��ü ���� �� �������� ���ϰ� ��.
public:
	CSoldier() {}
	~CSoldier() {}
};