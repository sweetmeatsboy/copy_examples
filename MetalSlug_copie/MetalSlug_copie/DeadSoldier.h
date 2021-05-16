#pragma once

class CDeadSoldier : public CSoldier
{
	//���ڸ����� ��ڰŸ��� �ֵ�.
public:
	static const RTTI m_Rtti;
	CAniDCSet* m_DeadSoldierAni;
private:
	int CurFrame;
	int MaxFrameCount;
	CSoldier* m_Parent;
	DWORD m_dwAniTimer;
public:
	void SetAniName(const TCHAR* _Name);
	void SetParentSoldier(CSoldier* _Parent);
private:
	/*
	28	����
	52 �Ϲ���
	53 �Ϲ���
	54 ������ ����?
	55 �Ϲ���
	56 �Ϲ���
	57 Į��?
	58 ������ ����?
	59 ��Ÿ���� -> ���÷��� �Ǵ� �÷��̾� ��ź���� ����.
	60 ������ ����
	62 ���÷����� ����.

	67 ������ִٰ� ���� �Ǵ� ������
	68 ����� �ִٰ� ���� �Ǵ� ������
	69 Į��
	70 Į��
	71 ������ִٰ� Į��
	72 Į��
	100  ��Ÿ�״� ��.
	*/
	void Progress_Dead_();
public:
	virtual void LineCollision();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something) {}
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CDeadSoldier() {}
	virtual ~CDeadSoldier() {}
};