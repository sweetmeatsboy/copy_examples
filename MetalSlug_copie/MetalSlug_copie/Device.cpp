#include "stdafx.h"



CDevice* CDevice::m_pInstance = NULL;

CDevice::CDevice(void)
{
}

CDevice::~CDevice(void)
{
	for (size_t i = 0; i < m_vecSoundBuff.size(); ++i)
	{
		m_vecSoundBuff[i]->Release();
	}
	m_vecSoundBuff.clear();
	m_pSound->Release();

}
void CDevice::PopMsgBox(const TCHAR* _contents, const TCHAR* _title)
{
	MessageBox(g_hWnd, _contents, _title, MB_OK);
}

HRESULT CDevice::Init(void)
{
	//���� ����̽� ����
	if (FAILED(DirectSoundCreate(NULL, &m_pSound, NULL)))
	{
		PopMsgBox(_T("�������̽���������"), _T("SYSTEM ERROR"));
		return E_FAIL;
	}

	//���� ����̽� �������� ����.
	if (FAILED(m_pSound->SetCooperativeLevel(g_hWnd, DSSCL_PRIORITY)))
	{
		PopMsgBox(_T("�������̽� �������� ����"), _T("SYSTEM ERROR"));
		return E_FAIL;
	}
	//���� ���⼭ �ѹ��� �ε�����.
	//BGM
	CDevice::GetInstance()->LoadWave(_T("../Sound/BGM/[BGM]boss_theme.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/BGM/[BGM]character_select.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/BGM/[BGM]Intro.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/BGM/[BGM]Stage_1.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/BGM/[BGM]Stage_2.wav"));

	//Enemy
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� ���� �Ǵ� �����׿� �����״� �Ҹ�]REBEL (9).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� ���÷��� �Ǵ� �ҿ� �״� �Ҹ�]REBEL (8).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� ���°�]DONALD MORDEN (3).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� �״¼Ҹ� 2]REBEL (7).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� �ѿ� �״� �Ҹ�]REBEL (6).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� �״� �Ҹ�]REBEL (4).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[���� Į�� �״� �Ҹ�]REBEL (5).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/[�÷��̾� �߰� �� ���� �Ҹ�]REBEL (2).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/MUMMY (1).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Enemy/MUMMY (2).wav"));

	//Item
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Item/FireBomb.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Item/FrameShot.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Item/HeavyMusinGun.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Item/ShotGun.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Item/�����̵�.wav"));

	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/NPC/[NPC_Helper]ThankYou.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/NPC/[NPC_Helper]����Ҷ�.wav"));

	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Player/[�״� �Ҹ�]FIO (1).wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Player/[�״¼Ҹ�]ERI (2).wav"));

	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/SelectedScene/SelectedEri.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/SelectedScene/SelectedGarma.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/SelectedScene/SelectedMarco.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/SelectedScene/SelectedFio.wav"));

	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Sys/FimalMission.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Sys/Mission.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Sys/Mission1_Start.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Sys/MissionComplete.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Sys/OhHo.wav"));
	CDevice::GetInstance()->LoadWave(_T("../Sound/EffectSound/Sys/Okey.wav"));




	return S_OK;
}

//���������� �б� �����Լ�(���)
HRESULT CDevice::LoadWave(const TCHAR* pFileName)
{
	HMMIO	hFile;
	//CreateFile
	//wave������ ����.
	hFile = mmioOpen(const_cast<TCHAR*>(pFileName), NULL, MMIO_READ);

	//��ũ����ü.
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	DSBUFFERDESC	BuffInfo;
	memset(&BuffInfo, 0, sizeof(DSBUFFERDESC));
	BuffInfo.dwBufferBytes = pChild.cksize;
	BuffInfo.dwSize = sizeof(DSBUFFERDESC);
	BuffInfo.dwFlags = DSBCAPS_STATIC;
	BuffInfo.lpwfxFormat = &wft;

	LPDIRECTSOUNDBUFFER		SoundBuff;

	if (FAILED(m_pSound->CreateSoundBuffer(&BuffInfo, &SoundBuff
		, NULL)))
	{
		PopMsgBox(_T("������ۻ�������"), _T(""));
		return E_FAIL;
	}

	void *pWrite1 = NULL, *pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	SoundBuff->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0);

	if (pWrite1 > 0)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 > 0)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	SoundBuff->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	m_vecSoundBuff.push_back(SoundBuff);

	return S_OK;
}

void CDevice::SoundPlay(int iIndex, DWORD dwFlag)
{
	if (iIndex < 0 || iIndex >(signed)m_vecSoundBuff.size())
		return;

	m_vecSoundBuff[iIndex]->SetCurrentPosition(0);

	DWORD			dwFre;

	m_vecSoundBuff[iIndex]->GetFrequency(&dwFre);
	m_vecSoundBuff[iIndex]->Play(0, 0, dwFlag);
}

void CDevice::SoundStop(int iIndex)
{
	if (iIndex < 0 || iIndex >(signed)m_vecSoundBuff.size())
		return;

	m_vecSoundBuff[iIndex]->Stop();



}

bool CDevice::SoundPlaying(int iIndex)
{
	DWORD	dwStatus = 0;
	m_vecSoundBuff[iIndex]->GetStatus(&dwStatus);

	if (dwStatus & DSBSTATUS_PLAYING)
		return true;
	return false;
}


