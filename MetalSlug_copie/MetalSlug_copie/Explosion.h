#pragma once


/*
 단순한 이팩트용 이미지를 뿌려준다.

 추후 시간이 남으면 보스전에서 쓰이는 Huge이팩트는 플레이어가 상승할 수 있도록 별개의 클래스로 만들자.
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