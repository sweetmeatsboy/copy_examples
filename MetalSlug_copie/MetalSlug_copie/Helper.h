#pragma once

class CHelper : public CCharacter
{
public:
	static const RTTI m_Rtti;
protected:	//���ΰ���.
	CLine* m_CurLine;
	CLine* SelectedLine;
	float LineOnPosPlayerY;

private:
	bool isDead;
	enum HELPER_PHASE
	{
		HAING,
		GIVE,
		RUN
	};
	//����� ������ �ִ� �������� Give�϶� 11���� ������.
	HELPER_PHASE m_Phase;
private:
	CAniDCSet* m_Ani;
	DWORD m_AniDelay;
	CW_Item* m_W_Item;
	CN_Item* m_N_Item;
	int GiveFrame;
	int m_CurFrame;
	bool m_Dir;
	DWORD m_PaternTimer;	//���� ������ �� �����ð����� �������� �̵��ϰ� �Ҷ� ���.
private:
	void ProgressHaing();
	void ProgressGive();
	void ProgressRun();
public:
	void isOutOfFocus();
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual void LineCollision();
	virtual const RTTI& GetRTTI() { return m_Rtti; }
public:
	virtual void InsertWeaonItem(const TCHAR* _Name);	//��ü ���� �� �������� ���ϰ� ��.
	virtual void InsertNomalItem(const TCHAR* _Item);	//��ü ���� �� �������� ���ϰ� ��.

public:
	CHelper(void) {}
	virtual ~CHelper(void) {}
};