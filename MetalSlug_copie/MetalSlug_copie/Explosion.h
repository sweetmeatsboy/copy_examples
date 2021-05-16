#pragma once


/*
 �ܼ��� ����Ʈ�� �̹����� �ѷ��ش�.

 ���� �ð��� ������ ���������� ���̴� Huge����Ʈ�� �÷��̾ ����� �� �ֵ��� ������ Ŭ������ ������.
*/


class CExplosion : public CObj
{
public:
	static const RTTI m_Rtti;
private:
	CAniDCSet* m_AniSet;
	int CurFrame;
	DWORD m_AniTimer;
public:
	void SetExplosionName(const char* _Name);
	const TCHAR* GetAniName()const { return m_AniSet->GetName(); }
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something) {}
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CExplosion() {}
	virtual ~CExplosion() {}
};