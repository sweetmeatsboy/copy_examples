#pragma once


class CPlayer : public CCharacter
{
public:
	static const RTTI m_Rtti;
private:
	enum PLAY_STATE
	{
		PLAYER_IDLE,
		PLAYER_APPEAR,			//Ư�� ��ġ�� �ÿ��̾ �����ϴ� �ִϸ��̼��� �Ѹ���.
		PLAYER_PLAY,
		PLAYER_DEAD,
		PLAYER_STATE_NONE
	};
	enum PLAYER_MODE
	{
		SLUG_MODE,
		HUMAN_MODE
	};
	PLAY_STATE m_PlayerState;		//�÷��̾� ������ �����ϱ� ���� �뵵.
	PLAYER_MODE m_PlayerMode;		//������ Ÿ�� �����׷�, ����̸� ������� �ٲ��ش�.
	PLAYER_TYPE m_Type;
private:
	CAniDCSet* m_AppearAni;
	int m_CurFrame;
	DWORD m_PaternTimer;
private:
	CPlayer* m_CurPlayer;		//���� �÷��̾� �ɸ���
	CPlayer* m_SparePlayer;		//���߿� �����׸� �������� ���� �뵵.
private:
	int ProgressIdle();
	int ProgressAppear();
	int ProgressPlay();
	int ProgressDead();
	int ProgressNone();
public:
	virtual void SetLine(list<CLine*>* _Line)
	{
		m_Line_List = _Line;
	}
public:
	void InsertPlayer(PLAYER_TYPE _Type);
	void SetPosCurPlayer(float _x, float _y) { m_CurPlayer->SetPos(_x, _y); }

	void AddScore(int _num) { m_Score += _num; }
	void AddBulletCount(int _num)
	{
		m_bulletCount += _num;
		if (m_bulletCount <= 0)
			m_bulletCount = 0;
	}
	void AddBomb(int _num)
	{
		m_BombCount += _num;
		if (m_BombCount <= 0)
			m_BombCount = 0;
	}
	void SetBulletCount(int _num) { m_bulletCount = _num; }
	void SetBombCount(int _num) { m_BombCount = _num; }

	int GetScore() const { return m_Score; }
	int GetBulletCount() const { return m_bulletCount; }
	int GetBombCount() const { return m_BombCount; }

private:
	int m_Score;			//���� ���ھ�.

	int m_bulletCount;		//���� ��ź ��.

	int m_BombCount;

	W_TYPE m_Weapon;		//���� ����
	const W_TYPE GetWeaponType()const { return m_Weapon; }
public:
	virtual void CheckCollision(CObj* _Something);
	virtual void LineCollision();

public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
	virtual const RTTI& GetRTTI() { return m_Rtti; }

public:
	CPlayer(void);
	~CPlayer(void);
};