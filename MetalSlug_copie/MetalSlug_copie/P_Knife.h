#pragma once

class CP_Knife : public CObj
{
public:
	static const RTTI m_Rtti;
public:
	int m_DeltaCount;
private:
	int Atk;
public:
	int GetAtk() const { return Atk; }
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CP_Knife() {}
	virtual ~CP_Knife() {}
};