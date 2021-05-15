#pragma once



class CAtkSoldier : public CSoldier
{
private:
	enum E_ActType
	{
		JUMP,
		STAND,
		SIT
	};
	E_ActType m_ActType;
public:
	static const RTTI m_Rtti;
	CAniDCSet* m_AtkSoldierAni;
private:
	int CurFrame;
	int MaxFrameCount;
	int m_AtkFrame;
	DWORD m_dwAniTimer;
	CSoldier * m_Parent;
public:
	void SetAniName(const TCHAR* _Name);
	void SetParentSoldier(CSoldier* _Parent);
	void FireToPlayer();
public:
	void Progress_AtkSoldier_29();//����ź
	void Progress_AtkSoldier_30();//����ź
	void Progress_AtkSoldier_32();//����ź
	void Progress_AtkSoldier_33();//������ ��ź
	void Progress_AtkSoldier_34();//����
	void Progress_AtkSoldier_35();//����
	void Progress_AtkSoldier_36();//��ź 2 ������ ��.
	void Progress_AtkSoldier_38();//�ڰ��� ��� ��.
	void Progress_AtkSoldier_40();//Į���ϴ� ��
	void Progress_AtkSoldier_41();//Į���ϴ� ��
	void Progress_AtkSoldier_42();//Į���ϴ� ��
	void Progress_AtkSoldier_77();//�����ϸ鼭 Į���ϴ� ��.
	void Progress_AtkSoldier_48();//�Ϲ�ź ��� ��
public:
	virtual void LineCollision();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	CAtkSoldier() {}
	virtual ~CAtkSoldier() {}
};
