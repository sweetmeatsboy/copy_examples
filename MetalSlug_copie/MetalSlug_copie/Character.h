#pragma once



class CCharacter : public CObj
{
public:
	static const RTTI m_Rtti;
protected:	//���ΰ���.
	CLine* m_CurLine;
	CLine* SelectedLine;
	float LineOnPosPlayerY;
public:	//���°���
	P_STATE m_P_STATE;
protected:	//�÷��̾� ������ �������� ���� ������.
	LONG	m_Score;

protected:
	list<CLine*>* m_Line_List;
	list<CLine*>::iterator m_Line_Pos;
	char tempStr[128];
public:
	virtual void Initialize(void) = 0;
	virtual int Progress(void) = 0;
	virtual void Render(HDC hdc) = 0;
	virtual void Release(void) = 0;
	virtual void CheckCollision(CObj* _Something) = 0;
	virtual void GetGravity();
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:

	virtual void SetLine(list<CLine*>* _Line) { m_Line_List = _Line; }
	virtual void UnSetLine() { m_Line_List = NULL; }

public:
	CCharacter(void) {}
	virtual ~CCharacter(void) {}
};