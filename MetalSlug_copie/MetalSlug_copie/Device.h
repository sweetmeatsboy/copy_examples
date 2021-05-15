#pragma once

// 사운드 관련 소스 확인 및 분석 해야할 곳

// 1. stdafx.h의 헤더파일 추가 부분
// 2. maingame 클래스 Initialize 및 Release 함수
// 3. Stage 클래스 Initialize 및 Progress 함수 
// 4. 프로젝트 폴더(하부 폴더로 Texture 폴더처럼 Sound폴더가 있는 지 확인)
// 5. 더불어서 wav파일만 지원되는 형식임. 
// 6. 혹여 집에서 작업하다가 안된다면 directx sdk의 문제임, 미 설치 시 인터넷에서 
//	  다운받아 필수적으로 설치해야 됨. june2010버전이 있고, 설치 후 끝다는 것이 아님.


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
		SFX_NPC_SIR,		//경례할 떄 나는 소리.
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
	//directx sdk (마이크로소프트에서 컴퓨터에있는 하드웨어를 쉽게 상요할수 있게
	// 여러가지 함수와, 데이터형을 제공해놓은 헤더파일과 라이브러리파일의 집합.)
	//다이렉트 사운드 인터페이스
	LPDIRECTSOUND				m_pSound; //사운드카드를 대표하는 객체.
	vector<LPDIRECTSOUNDBUFFER> m_vecSoundBuff;	//사운드파일을 로드해서 저장할 벡터

public:
	HRESULT Init(void);	// 장치를 초기화 하는역활.
	HRESULT LoadWave(const TCHAR* pFileName);	//파일경로를 통해 파일을 읽어 드리겠다.
	void SoundPlay(int iIndex /*몇번째 파일을 재생할래?*/, DWORD dwFlag/*무한루프, 한번*/); //파일을 재생 하겠다.
	void SoundStop(int iIndex);
	bool SoundPlaying(int iIndex);	// 현재 iIndex번째 사운드가 재생되고있는지 아닌지.

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
