#pragma once

// ���� ���� �ҽ� Ȯ�� �� �м� �ؾ��� ��

// 1. stdafx.h�� ������� �߰� �κ�
// 2. maingame Ŭ���� Initialize �� Release �Լ�
// 3. Stage Ŭ���� Initialize �� Progress �Լ� 
// 4. ������Ʈ ����(�Ϻ� ������ Texture ����ó�� Sound������ �ִ� �� Ȯ��)
// 5. ���Ҿ wav���ϸ� �����Ǵ� ������. 
// 6. Ȥ�� ������ �۾��ϴٰ� �ȵȴٸ� directx sdk�� ������, �� ��ġ �� ���ͳݿ��� 
//	  �ٿ�޾� �ʼ������� ��ġ�ؾ� ��. june2010������ �ְ�, ��ġ �� ���ٴ� ���� �ƴ�.


class CDevice
{
public:
	enum SounNAme
	{
		BGM_BOSS,
		BGM_SELECTED,
		BGM_INTRO,
		BGM_STAGE_1,
		BGM_STAGE_2,
		SFX_ENEMY_DEAD_SHOTGUN,
		SFX_ENEMY_DEAD_FIRE,
		SFX_ENEMY_LAUGHT,
		SFX_ENEMY_DEAD_BULLET_1,
		SFX_ENEMY_DEAD_BULLET_2,
		SFX_ENEMY_DEAD_BULLET_3,
		SFX_ENEMY_DEAD_KNIFE,
		SFX_ENEMY_SURPRISED,
		SFX_ENEMY_MUMMY_1,
		SFX_ENEMY_MUMMY_2,
		SFX_ITEM_FIREBOMB,
		SFX_ITEM_FRAMESHOT,
		SFX_ITEM_HEAVUMUSINGUN,
		SFX_ITEM_SHOTGUN,
		SFX_ITEM_BURNADE,
		SFX_NPC_THANKYOU,
		SFX_NPC_SIR,		//����� �� ���� �Ҹ�.
		SFX_PLAYER_DEAD_ERI,
		SFX_PLAYER_DEAD_FIO,
		SFX_SELECTE_ERI,
		SFX_SELECTE_FIO,
		SFX_SELECTE_GARMA,
		SFX_SELECTE_MARCO,
		SFX_SYS_FINALMISSION,
		SFX_SYS_MISSOIN,
		SFX_SYS_MISSION_1_START,
		SFX_SYS_MISSION_COMPLETE,
		SFX_SYS_OHHO,
		SFX_SYS_OKEY
	};
private:
	//directx sdk (����ũ�μ���Ʈ���� ��ǻ�Ϳ��ִ� �ϵ��� ���� ����Ҽ� �ְ�
	// �������� �Լ���, ���������� �����س��� ������ϰ� ���̺귯�������� ����.)
	//���̷�Ʈ ���� �������̽�
	LPDIRECTSOUND				m_pSound; //����ī�带 ��ǥ�ϴ� ��ü.
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;	//���������� �ε��ؼ� ������ ����

public:
	HRESULT Init(void);	// ��ġ�� �ʱ�ȭ �ϴ¿�Ȱ.
	HRESULT LoadWave(const TCHAR* pFileName);	//���ϰ�θ� ���� ������ �о� �帮�ڴ�.
	void SoundPlay(int iIndex /*���° ������ ����ҷ�?*/, DWORD dwFlag/*���ѷ���, �ѹ�*/); //������ ��� �ϰڴ�.
	void SoundStop(int iIndex);
	bool SoundPlaying(int iIndex);	// ���� iIndex��° ���尡 ����ǰ��ִ��� �ƴ���.

private:
	static CDevice* m_pInstance;

public:
	static inline CDevice* GetInstance(void)
	{
		if (m_pInstance == NULL)
		{
			m_pInstance = new CDevice;
			m_pInstance->Init();
		}
		return m_pInstance;
	}
public:
	inline void DestroyInst(void)
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = NULL;
		}
	}

private:
	CDevice(void);
	~CDevice(void);
private:
	void PopMsgBox(const TCHAR* contents, const TCHAR* _title);
};
