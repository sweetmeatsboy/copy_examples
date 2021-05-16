#pragma once

class CHelper : public CCharacter
{
public:
	static const RTTI m_Rtti;
protected:	//라인관련.
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
	//참고로 아이템 주는 프레임은 Give일때 11번쨰 프레임.
	HELPER_PHASE m_Phase;
private:
	CAniDCSet* m_Ani;
	DWORD m_AniDelay;
	CW_Item* m_W_Item;
	CN_Item* m_N_Item;
	int GiveFrame;
	int m_CurFrame;
	bool m_Dir;
	DWORD m_PaternTimer;	//행잉 상태일 떄 일정시간동안 한쪽으로 이동하게 할때 사용.
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
	virtual void InsertWeaonItem(const TCHAR* _Name);	//객체 생성 시 아이템을 지니게 함.
	virtual void InsertNomalItem(const TCHAR* _Item);	//객체 생성 시 아이템을 지니게 함.

public:
	CHelper(void) {}
	virtual ~CHelper(void) {}
};