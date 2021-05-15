#pragma once
#include "RTTI.h"
class CAniDCSet;

class CW_Item : public CObj
{
public:
	static const RTTI m_Rtti;
public:
	const TCHAR* GetWeaponItemName()const;
	void SetWeaponItemName(const TCHAR* _Name);

	bool isDead;
protected:
	CAniDCSet* m_Ani;
	int m_CurFrame;
	DWORD m_AniTimer;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual void CheckCollision(CObj* _Something);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CW_Item() {}
	virtual ~CW_Item() {}
};