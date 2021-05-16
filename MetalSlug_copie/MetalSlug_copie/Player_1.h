#pragma once

class CPlayer_1 : public CPlayer
{
public:
	static const RTTI m_Rtti;
public:
	CPlayer* m_Parent;
	void SetParent(CPlayer* _Parent) { m_Parent = _Parent; }
public:
	virtual void LineCollision();
	virtual void CheckCollision(CObj* _Something);
private:
	bool isMuJeok;
private:	//�浹ó�� ���� �κ�.
	//�÷��̾ �������ϴ� �浹ó�� ���� �κ�
	//�����۰� �浹
	//������ �浹
	//���� ����� �浹
	//�����׿��� �浹
	//�μ��� �ִ� ���ڰ��� ������Ʈ��. (�̶� ���⸦ Į�� �ٲ���� ��.)
	void CollisionWithWeaponItem(CObj* _Something);
	void CollisionWithNomalItem(CObj* _Something);
	void CollisionWithEnemy(CObj* _Something);
	void CollisionWithEnemyWeapon(CObj* _Something);
	void CollisionWithSlug(CObj* _Something);
	void CollisionWithObject(CObj* _Something);
private:	// �������
	CPt m_Posin;
	DWORD m_WeaponDelay;
	DWORD m_WeaponTimer;
	W_TYPE m_Weapon;
	virtual void KeyInput(void);
protected:	//���� ���� ����.
	KEY_INPUT m_DirKeyInput;
	ATK_STATE m_Atk_State;
	STAND_STATE m_Stand_State;
public: //�ִϸ��̼� ����
	bool m_isKnifeAtk;	//���� ���� �� �ش� ���� �ٲ�.
	bool m_isLeft;		//�ɸ����� ���⼺�� ��Ÿ��. ������ ���ϸ� true
	bool isDead;
	//��ü���´� KEY_INPUT���� ���� ����Ѵ�.
	BODY_STATE m_Body_State;
	CAniDCSet* m_BodyAni;
	void ControllBodyState();
	void SelectBodyAni();	//���� �ٵ� ���¿� �´� �ִϸ��̼��� SEt����.
	void SetBodyAni(const TCHAR* _AniName);
	void UpdateBodyAni();
	int m_CurBodyFrame;
	DWORD m_dwBodyTimer;

	LEG_STATE m_Leg_State;
	CAniDCSet* m_LegAni;
	void ControllLegState();
	void SelectLegAni();	//���� �ٸ� ���¿� �´� �ִϸ��̼��� SEt����.
	void SetLegAni(const TCHAR* _AniName);
	void UpdateLegAni();
	int m_CurLegFrame;
	DWORD m_dwLegTimer;

	SIT_STATE m_Sit_State;
	CAniDCSet* m_SitAni;
	void ControllSitState();
	void SelectSitAni();	//���� ���� �ڼ� ���¿� �´� �ִϸ��̼��� SEt����.
	void SetSitAni(const TCHAR* _AniName);
	void UpdateSitAni();
	int m_CurSitFrame;
	DWORD m_dwSitTimer;	//��� ���� ���·� �ٲ� �� GEtitck()����� ��.

	TCHAR tempStr[128];
public:	//����� ��� ���� �Լ���.
	void ViewPlayerInfo(HDC _hdc);		//�׽�Ʈ�� ���� �����ִ� ��,
	void SelectWeapon();			//���� Ű�Է����� ���ù޴� �Լ�.
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CPlayer_1(void);
	~CPlayer_1(void);
};