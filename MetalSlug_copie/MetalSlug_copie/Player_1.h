#pragma once

class CPlayer_1 : public CPlayer
{
public:
	static const RTTI m_Rtti;
public:
	CPlayer* m_Parent;
	void SetParent(CPlayer* _Parent) { m_Parent = _Parent; }
public:
	virtual void LineCollision();
	virtual void CheckCollision(CObj* _Something);
private:
	bool isMuJeok;
private:	//충돌처리 관련 부분.
	//플레이어가 가져야하는 충돌처리 관련 부분
	//아이템과 충돌
	//적과의 충돌
	//적의 무기와 충돌
	//슬러그와의 충돌
	//부술수 있는 상자같은 오브젝트들. (이때 무기를 칼로 바꿔줘야 함.)
	void CollisionWithWeaponItem(CObj* _Something);
	void CollisionWithNomalItem(CObj* _Something);
	void CollisionWithEnemy(CObj* _Something);
	void CollisionWithEnemyWeapon(CObj* _Something);
	void CollisionWithSlug(CObj* _Something);
	void CollisionWithObject(CObj* _Something);
private:	// 무기관련
	CPt m_Posin;
	DWORD m_WeaponDelay;
	DWORD m_WeaponTimer;
	W_TYPE m_Weapon;
	virtual void KeyInput(void);
protected:	//상태 관련 값들.
	KEY_INPUT m_DirKeyInput;
	ATK_STATE m_Atk_State;
	STAND_STATE m_Stand_State;
public: //애니메이션 관련
	bool m_isKnifeAtk;	//적이 근접 시 해당 값이 바뀜.
	bool m_isLeft;		//케릭터의 방향성을 나타냄. 왼쪽을 향하면 true
	bool isDead;
	//상체상태는 KEY_INPUT으로 같이 사용한다.
	BODY_STATE m_Body_State;
	CAniDCSet* m_BodyAni;
	void ControllBodyState();
	void SelectBodyAni();	//현재 바디 상태에 맞는 애니메이션을 SEt해줌.
	void SetBodyAni(const TCHAR* _AniName);
	void UpdateBodyAni();
	int m_CurBodyFrame;
	DWORD m_dwBodyTimer;

	LEG_STATE m_Leg_State;
	CAniDCSet* m_LegAni;
	void ControllLegState();
	void SelectLegAni();	//현재 다리 상태에 맞는 애니메이션을 SEt해줌.
	void SetLegAni(const TCHAR* _AniName);
	void UpdateLegAni();
	int m_CurLegFrame;
	DWORD m_dwLegTimer;

	SIT_STATE m_Sit_State;
	CAniDCSet* m_SitAni;
	void ControllSitState();
	void SelectSitAni();	//현재 앉은 자세 상태에 맞는 애니메이션을 SEt해줌.
	void SetSitAni(const TCHAR* _AniName);
	void UpdateSitAni();
	int m_CurSitFrame;
	DWORD m_dwSitTimer;	//얘는 앉은 상태로 바꿀 때 GEtitck()해줘야 함.

	TCHAR tempStr[128];
public:	//디버깅 모드 관련 함수들.
	void ViewPlayerInfo(HDC _hdc);		//테스트용 정보 보여주는 곳,
	void SelectWeapon();			//무기 키입력으로 선택받는 함수.
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CPlayer_1(void);
	~CPlayer_1(void);
};