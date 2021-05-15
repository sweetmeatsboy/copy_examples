#pragma once

class CUIMgr
{
private:		//플레이어와 관련된 정보들
	int m_Score;
	DWORD m_PlayTimer;
	int m_PlayTime;
	int m_Credit;
	int m_LifeCount;
	char m_Life[30];
	GAME_STATE m_Game_State;	//게임 진행중인지 결과창을 보여줘야 하는지를 구분한다.
	bool m_MissionEnded;
	CPlayer* m_Player;
	CCamera* m_Cam;
private:
	CWeaponBox m_WeaponBox;
	CTextBox m_ScoreText;
	CTextBox m_Lifetext;
	CTextBox m_TimeText;
	CTextBox m_CreditText;
	CTextBox m_InsertCoin;	//2P위치에 InsertCoin 띄움.
private:
	static CUIMgr* inst;
	CUIMgr() {}
	~CUIMgr() {}
public:
	static CUIMgr* Getinst()
	{
		if (inst == NULL)
		{
			inst = new CUIMgr();
			inst->Initialize();
		}
		return inst;
	}
	static void DestroyInst()
	{
		if (inst != NULL)
		{
			inst->Release();
			delete inst;
		}
		inst = NULL;
	}
public:
	void SetGameState(GAME_STATE _State);
	void SetCam(CCamera* _Cam);
	void SetPlayer(CPlayer* _Player);
	bool GetMissionEnded()const;
	void SetMissionEnded(bool _isEnded);
public:
	void Initialize();
	void Progress();
	void Render(HDC _hdc);
	void RenderMission(HDC _hdc);
	void RenderResult(HDC _hdc);
	void Release();
};
