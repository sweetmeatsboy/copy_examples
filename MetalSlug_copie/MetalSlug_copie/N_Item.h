#pragma once


class CN_Item : public CObj
{
public:
	static const RTTI m_Rtti;
public:
	N_ITEM_TYPE GetNomalItemType()const;
	void SetNomalItemName(const TCHAR* _Type);
private:	//�ִϸ��̼� ���õǼ� �ʿ��� ������.
	int CountNum;	//Ư������ �ִϸ��̼� �ݺ�Ƚ���� ���.
	int CurCount;
	int m_FirstLoopStartFrame;
	int m_FirstLoopEndedFrame;
	DWORD DisapointedTimer;
	DWORD m_dwDisapointTime;
	CAniDCSet* m_Ani;
	bool isLastLoop;

	int Score;
	int m_CurFrame;
	int m_MaxFrame;
	DWORD m_dwFrameTimer;
protected:
	bool isCollision;	//�÷��̾ �Ծ��� ��츦 �˷���.
	char tempStr[128];
	N_ITEM_TYPE m_N_ITEM_TYPE;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC _hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CN_Item() {}
	virtual ~CN_Item() {}
};