#include "stdafx.h"

const RTTI CPlayer_1::m_Rtti("CPlayer_1", CPlayer::m_Rtti);

CPlayer_1::CPlayer_1(void)
{
}

CPlayer_1::~CPlayer_1(void)
{
	Release();
}

void CPlayer_1::Initialize(void)
{
	//������ ������ �ʱ�ȭ �κ�
	SelectedLine = NULL;
	m_Line_List = NULL;
	///////////////////////
	//��ü ���� ��ǥ ����.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 30;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;
	//���µ� ���� ������ �ʱ�ȭ
	m_Atk_State = ATK_STATE_IDLE;
	m_P_STATE = P_IDLE;
	m_Leg_State = LEG_IDLE;
	m_Body_State = BODY_IDLE;
	m_Stand_State = STAND_IDLE;
	//���⤵�� �ʱ�ȭ
	m_isLeft = false;
	//������� �ʱ�ȭ.
	m_Weapon = W_NOMAL;	//�⺻ ���� �������� ����.
	m_WeaponTimer = GetTickCount();

	memset(tempStr, 0, sizeof(tempStr));
	//��ü ���ΰ���
	LineOnPosPlayerY = NULL;

	m_WeaponDelay = DWORD(SECOND * 0.5f);
	m_WeaponTimer = (DWORD)300.f;

	m_isKnifeAtk = false;
	//��ü �ִϸ��̼� �κ�.
	m_BodyAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("BODY_IDLE"));
	m_dwBodyTimer = GetTickCount();
	m_CurBodyFrame = 0;

	//��ü �ִϸ��̼� ���� �κ�
	m_LegAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("LEG_IDLE"));
	m_dwLegTimer = GetTickCount();
	m_CurLegFrame = 0;
	//���� �ڼ� 
	m_Sit_State = SIT_IDLE;
	m_SitAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_T("SIT_IDLE"));
	m_CurSitFrame = 0;

	m_Posin.setX(m_tInfo.fX + 30.f);
	m_Posin.setY(m_tInfo.fY);
	m_Sit_State = SIT_IDLE;

	isMuJeok = false;
	isDead = false;
}

int CPlayer_1::Progress(void)
{
	if (isDead == true)
		return 1;
	m_Posin.setX(float(m_tInfo.fX + 30.f*cosf(m_fAngle*(3.14f) / 180.f)));
	m_Posin.setY(float(m_tInfo.fY - 30.f*sinf(m_fAngle*(3.14f) / 180.f)));

	GetGravity();
	if (m_P_STATE == P_JUMPING && m_Speed_Y >= 0)
		m_P_STATE = P_LANDING;
	LineCollision();
	SelectWeapon();
	KeyInput();

	if (m_Stand_State == STAND_IDLE)
	{
		m_CurSitFrame = 0;
		m_Sit_State = SIT_NONE;

		ControllLegState();
		SelectLegAni();
		UpdateLegAni();
		ControllBodyState();
		SelectBodyAni();
		UpdateBodyAni();
	}
	else
	{	//���� ���¿��� ��Ʈ�� ���� �͵�.
		m_CurBodyFrame = 0;
		m_Body_State = BODY_NONE;
		m_CurLegFrame = 0;
		m_Leg_State = LEG_NONE;

		ControllSitState();
		SelectSitAni();
		UpdateSitAni();
	}

	m_Parent->SetPos(m_CenterPoint.getX(), m_CenterPoint.getY() + m_Speed_Y);
	SetPos(m_CenterPoint.getX(), m_CenterPoint.getY() + m_Speed_Y);
	//���µ��� ���α׷��� ������ ��� �ʱ�ȭ���ش�.
	//m_Body_State = BODY_IDLE;
	//m_Leg_State = LEG_IDLE;
	return 0;
}

void CPlayer_1::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f));*/

	if (m_Stand_State == STAND_IDLE)
	{
		m_LegAni->RenderAniSet(_hdc, m_CurLegFrame, m_tInfo.fX, m_tInfo.fY, m_isLeft);
		m_BodyAni->RenderAniSet(_hdc, m_CurBodyFrame, m_tInfo.fX, m_tInfo.fY, m_isLeft);
	}
	else
	{	//�����ڼ� �ִϸ��̼� ��.
		m_SitAni->RenderAniSet(_hdc, m_CurSitFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), m_isLeft);
	}
	Ellipse(_hdc,
		int(m_CenterPoint.getX() - 4), int(m_CenterPoint.getY() - 4),
		int(m_CenterPoint.getX() + 4), int(m_CenterPoint.getY() + 4));

	MoveToEx(_hdc, (int)m_tInfo.fX, (int)m_tInfo.fY, NULL);
	LineTo(_hdc, (int)m_Posin.getX(), (int)m_Posin.getY());

	ViewPlayerInfo(_hdc);
}
void CPlayer_1::UpdateLegAni()
{
	if (GetTickCount() - m_dwLegTimer > m_LegAni->GetFrameDelay(m_CurLegFrame))
	{
		m_dwLegTimer = GetTickCount();
		++m_CurLegFrame;
		if (m_CurLegFrame >= m_LegAni->GetFrameCount())
		{
			//if(m_LegAni->GetReplayer())
			//	m_CurLegFrame = m_LegAni->GetReplayFrameNum();
			//else
			//{
			m_CurLegFrame = 0;
			m_Leg_State = LEG_IDLE;
			//}
		}
	}
}
void CPlayer_1::UpdateBodyAni()
{
	if (GetTickCount() - m_dwBodyTimer > m_BodyAni->GetFrameDelay(m_CurBodyFrame))
	{
		m_dwBodyTimer = GetTickCount();
		++m_CurBodyFrame;
		if (m_CurBodyFrame >= m_BodyAni->GetFrameCount())
		{
			//if(m_BodyAni->GetReplayer())
			//	m_CurBodyFrame = m_BodyAni->GetReplayFrameNum();
			//else
			//{
			m_CurBodyFrame = 0;
			m_Body_State = BODY_IDLE;
			//}
		}
	}
}

void CPlayer_1::UpdateSitAni()
{
	if (GetTickCount() - m_dwSitTimer > m_SitAni->GetFrameDelay(m_CurSitFrame))
	{
		m_dwSitTimer = GetTickCount();
		++m_CurSitFrame;
		if (m_CurSitFrame >= m_SitAni->GetFrameCount())
		{
			//if(m_BodyAni->GetReplayer())
			//	m_CurBodyFrame = m_BodyAni->GetReplayFrameNum();
			//else
			//{
			m_CurSitFrame = 0;
			m_Sit_State = SIT_IDLE;
			//}
		}
	}
}
void CPlayer_1::ViewPlayerInfo(HDC _hdc)
{
	memset(tempStr, 0, sizeof(tempStr));
	if (SelectedLine != NULL)
	{
		wsprintf(tempStr, _T("L_LX : %d, L_LY : %d"), SelectedLine->m_lPoint.x, SelectedLine->m_lPoint.y);
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 70, tempStr, wcslen(tempStr));
	}
	memset(tempStr, 0, sizeof(tempStr));
	if (P_LAND == m_P_STATE)
	{
		wsprintf(tempStr, _T("P_STATE : LAND"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 10, tempStr, wcslen(tempStr));
	}
	if (P_IDLE == m_P_STATE)
	{
		wsprintf(tempStr, _T("P_STATE : IDLE"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 10, tempStr, wcslen(tempStr));
	}
	if (P_JUMP == m_P_STATE)
	{
		wsprintf(tempStr, _T("P_STATE : JUMP"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 10, tempStr, wcslen(tempStr));
	}
	if (P_LANDING == m_P_STATE)
	{
		wsprintf(tempStr, _T("P_STATE : LANDING"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 10, tempStr, wcslen(tempStr));
	}
	if (P_JUMPING == m_P_STATE)
	{
		wsprintf(tempStr, _T("P_STATE : JUMPING"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 10, tempStr, wcslen(tempStr));
	}

	memset(tempStr, 0, sizeof(tempStr));
	if (KEY_IDLE == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_IDLE"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_UP == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_UP"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_UP_TO_RIGHT == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_UP_TO_RIGHT"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_RIGHT_TO_UP == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_RIGHT_TO_UP"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_RIGHT == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_RIGHT"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_RIGHT_TO_DOWN == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_RIGHT_TO_DOWN"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_DOWN_TO_RIGHT == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_DOWN_TO_RIGHT"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_DOWN == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_DOWN"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_LEFT_TO_DOWN == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_LEFT_TO_DOWN"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_LEFT == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_LEFT"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_LEFT_TO_UP == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_LEFT_TO_UP"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	if (KEY_UP_TO_LEFT == m_DirKeyInput)
	{
		wsprintf(tempStr, _T("KEY_INPUT : KEY_UP_TO_LEFT"));
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 30, tempStr, wcslen(tempStr));
	}
	memset(tempStr, 0, sizeof(tempStr));
	if (m_Body_State != BODY_NONE)
	{
		wsprintf(tempStr, _T("BODY_ANI NAME : %s"), m_BodyAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 50, tempStr, wcslen(tempStr));
		memset(tempStr, 0, sizeof(tempStr));
		wsprintf(tempStr, _T("LEG_ANI NAME : %s"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 70, tempStr, wcslen(tempStr));
		memset(tempStr, 0, sizeof(tempStr));
	}
	if (m_Sit_State != SIT_NONE)
	{
		wsprintf(tempStr, _T("SIT_ANI NAME : %s"), m_SitAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 50, tempStr, wcslen(tempStr));
	}
	memset(tempStr, 0, sizeof(tempStr));
	if (m_Weapon == W_KNIFE)
	{
		wsprintf(tempStr, _T("m_Weapon : KNIFE"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}
	else if (m_Weapon == W_NOMAL)
	{
		wsprintf(tempStr, _T("m_Weapon : NOMAL"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}
	else if (m_Weapon == W_S)
	{
		wsprintf(tempStr, _T("m_Weapon : SHOTGUN"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}
	else if (m_Weapon == W_H)
	{
		wsprintf(tempStr, _T("m_Weapon : H"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}
	else if (m_Weapon == W_F)
	{
		wsprintf(tempStr, _T("m_Weapon : F"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}
	else if (m_Weapon == W_BOMB)
	{
		wsprintf(tempStr, _T("m_Weapon : BOMB"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}
	else
	{
		wsprintf(tempStr, _T("m_Weapon : SOME WEAPON"), m_LegAni->GetName());
		TextOut(_hdc, (int)m_CenterPoint.getX(), (int)m_CenterPoint.getY() + 90, tempStr, wcslen(tempStr));
	}

}
void CPlayer_1::Release(void)
{
	m_Line_List = NULL;
}
void CPlayer_1::ControllSitState()
{
	if (m_Stand_State == STAND_SIT)
	{
		if (m_Atk_State == ATK_STATE_ATK)	//���� ���¿������� ���� ��.
		{
			if (m_Weapon == W_KNIFE)
				m_Sit_State = SIT_KNIFE;
			else if (m_Weapon == W_NOMAL)
				m_Sit_State = SIT_SHOOT_NORMAL;
			else if ((m_Weapon == W_H) || (m_Weapon == W_S) || (m_Weapon == W_F))
				m_Sit_State = SIT_SHOOT_NORMAL;
			else if (m_Weapon == W_BOMB)
				m_Sit_State = SIT_BOMB;
		}
		else	//�ܼ� �ɾƼ� �ִ� ����.
		{
			if (m_DirKeyInput == KEY_IDLE)
				m_Sit_State = SIT_IDLE;
			else
				m_Sit_State = SIT_RUN;
		}
	}
}
void CPlayer_1::SelectSitAni()	//���� ���� �ڼ� ���¿� �´� �ִϸ��̼��� SEt����.
{
	if (m_Sit_State == SIT_IDLE)
	{
		if (wcscmp(m_SitAni->GetName(), _T("SIT_IDLE")) != 0)
			SetSitAni(_T("SIT_IDLE"));
	}
	if (m_Sit_State == SIT_RUN)
	{
		if (wcscmp(m_SitAni->GetName(), _T("SIT_")) != 0)
			SetSitAni(_T("SIT_IDLE"));
	}
	if (m_Sit_State == SIT_KNIFE)
	{
		if (wcscmp(m_SitAni->GetName(), _T("SIT_SHOOT_KNIFE")) != 0)
			SetSitAni(_T("SIT_SHOOT_KNIFE"));
	}
	if (m_Sit_State == SIT_SHOOT_NORMAL)
	{
		if (wcscmp(m_SitAni->GetName(), _T("SIT_SHOOT_NOMAL"))!= 0)
			SetSitAni(_T("SIT_SHOOT_NOMAL"));
	}
	if (m_Sit_State == SIT_BOMB)
	{
		if (wcscmp(m_SitAni->GetName(), _T("SIT_SHOOT_BOMB")) != 0)
			SetSitAni(_T("SIT_SHOOT_BOMB"));
	}
}
void CPlayer_1::SetSitAni(const TCHAR* _AniName)
{
	m_CurSitFrame = 0;
	m_SitAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_AniName);
}

void CPlayer_1::SelectWeapon()
{

	if (GetAsyncKeyState('1'))		//����
		m_Weapon = W_NOMAL;
	if (GetAsyncKeyState('2'))		//Į
		m_Weapon = W_KNIFE;
	if (GetAsyncKeyState('3'))		//��ź
		m_Weapon = W_BOMB;
	if (GetAsyncKeyState('4'))		//�ӽŰ�
		m_Weapon = W_H;
	if (GetAsyncKeyState('5'))		//�����Ӽ�
		m_Weapon = W_F;
	if (GetAsyncKeyState('6'))		//����
		m_Weapon = W_S;
}

void CPlayer_1::KeyInput(void)
{
	if (m_Weapon == W_NOMAL)
		m_WeaponDelay = 230;
	if (m_Weapon == W_KNIFE)
		m_WeaponDelay = 230;
	if (m_Weapon == W_H)
		m_WeaponDelay = 75;
	if (m_Weapon == W_S)
		m_WeaponDelay = 300;
	if (m_Weapon == W_F)
		m_WeaponDelay = 300;
	if (m_Weapon == W_BOMB)
		m_WeaponDelay = 300;

	if (GetAsyncKeyState('P'))
		isMuJeok = !isMuJeok;

	if (GetAsyncKeyState('S'))	//����
	{
		//���� �������°� �ƴ϶�� �������·� �ٲ����� 
		//���� ���� �����ش�.	
		if (m_Sit_State != SIT_NONE)	//���� �����϶�
		{
		}
		else
		{
			if (P_LAND == m_P_STATE)
			{
				m_Speed_Y = -18.f;
				m_P_STATE = P_JUMPING;
				if (m_Sit_State != SIT_NONE)
					m_Sit_State = SIT_NONE;
			}
		}
	}

	if (GetAsyncKeyState('D'))	//��[����]
	{
		m_Atk_State = ATK_STATE_ATK;
		if (m_Parent->GetBulletCount() == 0)
			m_Weapon = W_NOMAL;

		if (m_Body_State == BODY_KNIFE || m_Sit_State == SIT_KNIFE)
		{
			if (GetTickCount() - m_WeaponTimer > 70)
			{
				m_WeaponTimer = GetTickCount();
				if (m_Body_State == BODY_KNIFE || m_Sit_State == SIT_KNIFE)
				{
					m_WeaponTimer = GetTickCount();
					CBulletMgr::Fire(
						m_Posin.getX(), m_Posin.getY(), m_fAngle, W_KNIFE, m_isLeft);
				}
			}
		}
		else
		{
			if (m_Body_State != BODY_IDLE)
			{
				if (m_Weapon == W_NOMAL)
					m_Body_State = BODY_SHOOT_NOMAL;
				else
				{
					if (m_Weapon != W_BOMB)
						m_Body_State = BODY_SHOOT_WEAPON_LEFT;
				}
			}
			if (GetTickCount() - m_WeaponTimer > m_WeaponDelay)
			{
				m_WeaponTimer = GetTickCount();
				CBulletMgr::Fire(
					m_Posin.getX(), m_Posin.getY(), m_fAngle, m_Weapon, m_isLeft);
				m_Parent->AddBulletCount(-1);
				if (m_Parent->GetBulletCount() == 0)
				{
					m_Parent->SetBulletCount(-1);
					m_Weapon = W_NOMAL;
				}
			}
		}
	}
	else if (GetAsyncKeyState('W'))	//��ź
	{
		m_Atk_State = ATK_STATE_ATK;
		if (m_Parent->GetBombCount() > 0)
		{
			if (GetTickCount() - m_WeaponTimer > 300)
			{
				m_WeaponTimer = GetTickCount();
				CBulletMgr::Fire(
					m_Posin.getX(), m_Posin.getY(), m_fAngle, W_BOMB, m_isLeft);
				m_Parent->AddBomb(-1);
			}
		}
		if (m_Body_State != BODY_NONE)
			m_Body_State = BODY_BOMB;
		if (m_Sit_State != SIT_NONE)
			m_Sit_State = SIT_BOMB;
	}
	else
	{
		m_Atk_State = ATK_STATE_IDLE;
	}
	if (m_fAngle > 360.f)
		m_fAngle -= 360.f;
	if (GetAsyncKeyState(VK_LEFT))
	{	//180���� ����.
		m_isLeft = true;
		m_CenterPoint.setX(m_CenterPoint.getX() - m_Speed_X);
		if (P_LAND == m_P_STATE || P_IDLE == m_P_STATE)
		{
			m_CenterPoint.setY(LineOnPosPlayerY);
		}
		if (m_fAngle <= 270 && m_fAngle >= 90.f)
		{
			if (m_fAngle > 180.f)
			{
				m_DirKeyInput = KEY_UP_TO_LEFT;
				m_fAngle -= 10.f;
			}
			else if (m_fAngle < 180.f)
			{
				m_DirKeyInput = KEY_DOWN_TO_LEFT;
				m_fAngle += 10.f;
			}
			if (m_fAngle >= 175.f && m_fAngle <= 185.f)
				m_fAngle = 180.f;
		}
		else
		{
			m_DirKeyInput = KEY_LEFT;
			m_fAngle = 180.f;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{	//0���� ����
		m_isLeft = false;
		m_CenterPoint.setX(m_CenterPoint.getX() + m_Speed_X);
		if (P_LAND == m_P_STATE || P_IDLE == m_P_STATE)
		{
			m_CenterPoint.setY(LineOnPosPlayerY);
		}
		if ((m_fAngle <= 90.f && m_fAngle >= 0.f) || (m_fAngle >= 270.f && m_fAngle < 360.f))
		{	//���� �����ؾߵ�.
			if (m_fAngle <= 90.f && m_fAngle > 0.f)
			{
				m_DirKeyInput = KEY_UP_TO_RIGHT;
				m_fAngle -= 10.f;
			}
			else if (m_fAngle >= 270.f && m_fAngle < 360.f)
			{
				m_DirKeyInput = KEY_DOWN_TO_RIGHT;
				m_fAngle += 10.f;
			}
			if (m_fAngle <= 5.f || m_fAngle >= 355.f)
			{
				m_DirKeyInput = KEY_RIGHT;
				m_fAngle = 0.f;
			}
		}
		else
		{
			m_DirKeyInput = KEY_RIGHT;
			m_fAngle = 0.f;
		}
	}
	else if (GetAsyncKeyState(VK_UP))
	{	//90���� ����.
		if (m_Sit_State != SIT_NONE)
			m_Sit_State = SIT_NONE;
		if (m_fAngle >= 0.f && m_fAngle <= 180.f)
		{
			if (m_fAngle <= 90.f)
			{
				m_DirKeyInput = KEY_LEFT_TO_UP;
				m_fAngle += 10.f;
			}
			else
			{
				m_DirKeyInput = KEY_RIGHT_TO_UP;
				m_fAngle -= 10.f;
			}
			if (m_fAngle <= 105.f && m_fAngle >= 85.f)
			{
				m_DirKeyInput = KEY_UP;
				m_fAngle = 90.f;
			}
		}
		else
		{
			m_DirKeyInput = KEY_UP;
			m_fAngle = 90.f;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{	//270���� ����.
		if (m_P_STATE == P_IDLE || m_P_STATE == P_LAND)
		{
			if (m_Body_State != BODY_NONE)
				m_Body_State = BODY_NONE;
			if (m_Sit_State == SIT_NONE)
				m_Sit_State = SIT_IDLE;

			m_Stand_State = STAND_SIT;
		}
		else
		{
			if (m_Sit_State != SIT_NONE)
				m_Sit_State = SIT_NONE;

			if ((m_fAngle >= 180.f && m_fAngle < 360.f) || m_fAngle == 0)
			{
				if (m_fAngle < 270.f && m_fAngle >= 180.f)
				{
					m_DirKeyInput = KEY_LEFT_TO_DOWN;
					m_fAngle += 10.f;
				}
				else if (m_fAngle > 270.f && m_fAngle < 360.f)
				{
					m_DirKeyInput = KEY_RIGHT_TO_DOWN;
					m_fAngle -= 10.f;
				}
				else if (m_fAngle == 0)
				{
					m_DirKeyInput = KEY_RIGHT_TO_DOWN;
					m_fAngle = 350.f;
				}
				if (m_fAngle >= 265.f && m_fAngle <= 275.f)
				{
					m_DirKeyInput = KEY_DOWN;
					m_fAngle = 270.f;
				}
			}
			else
			{
				m_DirKeyInput = KEY_DOWN;
				m_fAngle = 270.f;
			}
		}
	}
	else
	{
		if (m_Body_State == BODY_NONE)
			m_Body_State = BODY_IDLE;
		if (m_Sit_State != SIT_NONE)
			m_Sit_State = SIT_NONE;

		m_Stand_State = STAND_IDLE;

		m_DirKeyInput = KEY_IDLE;
		if (m_isLeft == true)
			m_fAngle = 180.f;
		else
			m_fAngle = 0.f;
	}
}

void CPlayer_1::ControllBodyState()
{
	if (m_Stand_State == STAND_IDLE)		//���Ŀ� ���� �ڼ��϶��� ������ ����� �Ѵ�.
	{
		if (m_Atk_State == ATK_STATE_ATK)
		{
			if (m_Weapon == W_NOMAL)	//�����϶�.
			{
				if ((m_DirKeyInput == KEY_LEFT) || (m_DirKeyInput == KEY_DOWN_TO_LEFT)
					|| (m_DirKeyInput == KEY_UP_TO_LEFT) ||
					(m_DirKeyInput == KEY_RIGHT) || (m_DirKeyInput == KEY_DOWN_TO_RIGHT)
					|| (m_DirKeyInput == KEY_UP_TO_RIGHT) || (m_DirKeyInput == KEY_IDLE))
					m_Body_State = BODY_SHOOT_NOMAL;

				if ((m_DirKeyInput == KEY_UP) || (m_DirKeyInput == KEY_RIGHT_TO_UP)
					|| (m_DirKeyInput == KEY_LEFT_TO_UP))
					m_Body_State = BODY_SHOOT_NOMAL_UP;

				if ((m_DirKeyInput == KEY_DOWN) || (m_DirKeyInput == KEY_RIGHT_TO_DOWN)
					|| (m_DirKeyInput == KEY_LEFT_TO_DOWN))
					m_Body_State = BODY_SHOOT_NOMAL_DOWN;
			}
			else if (m_Weapon == W_KNIFE)	// Į �϶�
			{
				/*if( (m_DirKeyInput == KEY_LEFT) || (m_DirKeyInput == KEY_DOWN_TO_LEFT)
				|| (m_DirKeyInput == KEY_UP_TO_LEFT) ||
				(m_DirKeyInput == KEY_RIGHT) || (m_DirKeyInput == KEY_DOWN_TO_RIGHT)
				|| (m_DirKeyInput == KEY_UP_TO_RIGHT) )*/
				m_Body_State = BODY_KNIFE;
			}
			else if (m_Weapon == W_BOMB)
			{
				m_Body_State = BODY_BOMB;
			}
			else	//�׿� �ӽŰ� ���� ������ ��.
			{
				if ((m_DirKeyInput == KEY_LEFT))
					m_Body_State = BODY_SHOOT_WEAPON_LEFT;
				if ((m_DirKeyInput == KEY_DOWN_TO_LEFT))
					m_Body_State = BODY_SHOOT_WEAPON_DOWN_TO_LEFT;
				if ((m_DirKeyInput == KEY_UP_TO_LEFT))
					m_Body_State = BODY_SHOOT_WEAPON_UP_TO_LEFT;

				if ((m_DirKeyInput == KEY_RIGHT))
					m_Body_State = BODY_SHOOT_WEAPON_RIGHT;
				if ((m_DirKeyInput == KEY_DOWN_TO_RIGHT))
					m_Body_State = BODY_SHOOT_WEAPON_DOWN_TO_RIGHT;
				if ((m_DirKeyInput == KEY_UP_TO_RIGHT))
					m_Body_State = BODY_SHOOT_WEAPON_UP_TO_RIGHT;

				if ((m_DirKeyInput == KEY_UP))
					m_Body_State = BODY_SHOOT_WEAPON_UP;
				if ((m_DirKeyInput == KEY_RIGHT_TO_UP))
					m_Body_State = BODY_SHOOT_WEAPON_RIGHT_TO_UP;
				if ((m_DirKeyInput == KEY_LEFT_TO_UP))
					m_Body_State = BODY_SHOOT_WEAPON_LEFT_TO_UP;

				if ((m_DirKeyInput == KEY_DOWN))
					m_Body_State = BODY_SHOOT_WEAPON_DOWN;
				if ((m_DirKeyInput == KEY_RIGHT_TO_DOWN))
					m_Body_State = BODY_SHOOT_WEAPON_RIGHT_TO_DOWN;
				if ((m_DirKeyInput == KEY_LEFT_TO_DOWN))
					m_Body_State = BODY_SHOOT_WEAPON_LEFT_TO_DOWN;
			}
		}
		else	//�������� �ƴ� ��.
		{
			if ((m_Weapon == W_NOMAL) || (m_Weapon == W_KNIFE))
			{
				if ((m_DirKeyInput == KEY_IDLE) && (m_Leg_State == LEG_IDLE))
				{
					m_Body_State = BODY_IDLE;
				}
				else if ((m_DirKeyInput == KEY_UP) || (m_DirKeyInput == KEY_LEFT_TO_UP)
					|| (m_DirKeyInput == KEY_RIGHT_TO_UP))
				{
					m_Body_State = BODY_LOOK_NOMAL_UP;
				}
				else if (
					(m_DirKeyInput == KEY_RIGHT) || (m_DirKeyInput == KEY_UP_TO_RIGHT)
					|| (m_DirKeyInput == KEY_DOWN_TO_RIGHT) ||
					(m_DirKeyInput == KEY_LEFT) || (m_DirKeyInput == KEY_UP_TO_LEFT)
					|| (m_DirKeyInput == KEY_DOWN_TO_LEFT))
				{
					if (m_Leg_State == LEG_RUN)
					{
						m_Body_State = BODY_RUN;
					}
					else if (m_Leg_State == LEG_DIR_JUMP)
					{
						m_Body_State = BODY_DIR_JUMP;
					}
				}
				else if ((m_DirKeyInput == KEY_DOWN) ||
					(m_DirKeyInput == KEY_LEFT_TO_DOWN) ||
					(m_DirKeyInput == KEY_RIGHT_TO_DOWN))
				{
					m_Body_State = BODY_LOOK_NOMAL_DOWN;
				}
			}
			else	//���⸦ ���� ������ ��.
			{
				if ((m_DirKeyInput == KEY_IDLE) && (m_Leg_State == LEG_IDLE))
				{
					m_Body_State = BODY_WEAPON_IDLE;
				}
				else if ((m_DirKeyInput == KEY_UP) || (m_DirKeyInput == KEY_LEFT_TO_UP)
					|| (m_DirKeyInput == KEY_RIGHT_TO_UP))
				{
					m_Body_State = BODY_LOOK_WEAPON_UP;
				}
				else if (
					(m_DirKeyInput == KEY_RIGHT) || (m_DirKeyInput == KEY_UP_TO_RIGHT)
					|| (m_DirKeyInput == KEY_DOWN_TO_RIGHT) ||
					(m_DirKeyInput == KEY_LEFT) || (m_DirKeyInput == KEY_UP_TO_LEFT)
					|| (m_DirKeyInput == KEY_DOWN_TO_LEFT))
				{
					if (m_Leg_State == LEG_RUN)
						m_Body_State = BODY_WEAPON_RUN;
					else if (m_Leg_State == LEG_DIR_JUMP)
						m_Body_State = BODY_WEAPON_DIR_JUMP;
				}
				else if ((m_DirKeyInput == KEY_DOWN) ||
					(m_DirKeyInput == KEY_LEFT_TO_DOWN) ||
					(m_DirKeyInput == KEY_RIGHT_TO_DOWN))
				{
					m_Body_State = BODY_LOOK_WEAPON_DOWN;
				}
			}
		}
	}
}

void CPlayer_1::SelectBodyAni()
{
	//////�����϶��� ���
	if (m_Body_State == BODY_IDLE)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_IDLE")) != 0)
			SetBodyAni(_T("BODY_IDLE"));
	}
	if (m_Body_State == BODY_RUN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_RUN")) != 0)
			SetBodyAni(_T("BODY_RUN"));
	}
	if (m_Body_State == BODY_BOMB)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_BOMB")) != 0)
			SetBodyAni(_T("BODY_SHOOT_BOMB"));
	}
	if (m_Body_State == BODY_KNIFE)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_KNIFE")) != 0)
			SetBodyAni(_T("BODY_SHOOT_KNIFE"));
	}
	if (m_Body_State == BODY_JUMP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_JUMP")) != 0)
			SetBodyAni(_T("BODY_JUMP"));
	}
	if (m_Body_State == BODY_DIR_JUMP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_DIR_JUMP")) != 0)
			SetBodyAni(_T("BODY_DIR_JUMP"));
	}

	if (m_Body_State == BODY_SHOOT_NOMAL_UP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_NOMAL_UP")) != 0)
			SetBodyAni(_T("BODY_SHOOT_NOMAL_UP"));
	}
	if (m_Body_State == BODY_SHOOT_NOMAL)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_NOMAL")) != 0)
			SetBodyAni(_T("BODY_SHOOT_NOMAL"));
	}
	if (m_Body_State == BODY_SHOOT_NOMAL_DOWN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_NOMAL_DOWN")) != 0)
			SetBodyAni(_T("BODY_SHOOT_NOMAL_DOWN"));
	}

	if (m_Body_State == BODY_LOOK_NOMAL_UP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_LOOK_NOMAL_UP")) != 0)
			SetBodyAni(_T("BODY_LOOK_NOMAL_UP"));
	}
	if (m_Body_State == BODY_LOOK_NOMAL_DOWN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_LOOK_NOMAL_DOWN")) != 0)
			SetBodyAni(_T("BODY_LOOK_NOMAL_DOWN"));
	}
	/////////////////////////////////////////////////////////////////////

	//���� �� ������ ���� ���� ���µ�.
	if (m_Body_State == BODY_WEAPON_IDLE)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_WEAPON_IDLE")) != 0)
			SetBodyAni(_T("BODY_WEAPON_IDLE"));
	}
	if (m_Body_State == BODY_WEAPON_RUN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_WEAPON_RUN")) != 0)
			SetBodyAni(_T("BODY_WEAPON_RUN"));
	}
	if (m_Body_State == BODY_WEAPON_JUMP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_WEAPON_JUMP")) != 0)
			SetBodyAni(_T("BODY_WEAPON_JUMP"));
	}
	if (m_Body_State == BODY_WEAPON_DIR_JUMP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_WEAPON_DIR_JUMP")) != 0)
			SetBodyAni(_T("BODY_WEAPON_DIR_JUMP"));
	}

	if (m_Body_State == BODY_LOOK_WEAPON_UP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_LOOK_WEAPON_UP")) != 0)
			SetBodyAni(_T("BODY_LOOK_WEAPON_UP"));
	}
	if (m_Body_State == BODY_LOOK_WEAPON_DOWN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_LOOK_WEAPON_DOWN")) != 0)
			SetBodyAni(_T("BODY_LOOK_WEAPON_DOWN"));
	}

	if (m_Body_State == BODY_SHOOT_WEAPON_UP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_UP")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_UP"));
	}

	if (m_Body_State == BODY_SHOOT_WEAPON_UP_TO_RIGHT)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_UP_TO_RIGHT")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_UP_TO_RIGHT"));
	}

	if (m_Body_State == BODY_SHOOT_WEAPON_UP_TO_LEFT)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_UP_TO_RIGHT")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_UP_TO_RIGHT"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_DOWN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_DOWN")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_DOWN"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_DOWN_TO_RIGHT)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_DOWN_TO_RIGHT")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_DOWN_TO_RIGHT"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_DOWN_TO_LEFT)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_DOWN_TO_RIGHT")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_DOWN_TO_RIGHT"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_RIGHT)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_RIGHT_TO_UP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_RIGHT_TO_UP")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_RIGHT_TO_UP"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_RIGHT_TO_DOWN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_RIGHT_TO_DOWN")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_RIGHT_TO_DOWN"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_LEFT)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_LEFT_TO_UP)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_RIGHT_TO_UP")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_RIGHT_TO_UP"));
	}
	if (m_Body_State == BODY_SHOOT_WEAPON_LEFT_TO_DOWN)
	{
		if (wcscmp(m_BodyAni->GetName(), _T("BODY_SHOOT_WEAPON_RIGHT_TO_DOWN")) != 0)
			SetBodyAni(_T("BODY_SHOOT_WEAPON_RIGHT_TO_DOWN"));
	}
}
void CPlayer_1::SetBodyAni(const TCHAR* _AniName)
{
	m_CurBodyFrame = 0;
	m_BodyAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_AniName);
}


void CPlayer_1::SelectLegAni()
{
	if (m_Leg_State == LEG_IDLE)
	{
		if (wcscmp(m_LegAni->GetName(), _T("LEG_IDLE")) != 0)
			SetLegAni(_T("LEG_IDLE"));
	}

	if (m_Leg_State == LEG_RUN)
	{
		if (wcscmp(m_LegAni->GetName(), _T("LEG_RUN")) != 0)
			SetLegAni(_T("LEG_RUN"));
	}
	if (m_Leg_State == LEG_JUMP)
	{
		if (wcscmp(m_LegAni->GetName(), _T("LEG_JUMP")) != 0)
			SetLegAni(_T("LEG_JUMP"));
	}
	if (m_Leg_State == LEG_DIR_JUMP)
	{
		if (wcscmp(m_LegAni->GetName(), _T("LEG_DIR_JUMP")) != 0)
			SetLegAni(_T("LEG_DIR_JUMP"));
	}
}
void CPlayer_1::SetLegAni(const TCHAR* _AniName)
{
	m_CurLegFrame = 0;
	m_LegAni = CAniInfoMgr::Getinst()->Getplayer_1_AniSet(_AniName);
}
void CPlayer_1::ControllLegState()
{
	if (true)		//���Ŀ� ���� �ڼ��϶��� ������ ����� �Ѵ�.
	{
		if ((P_LAND == m_P_STATE) || (P_IDLE == m_P_STATE))
		{		//�����¿� �ȴ� ���
			if ((KEY_IDLE == m_DirKeyInput) || (KEY_UP == m_DirKeyInput) || (KEY_DOWN == m_DirKeyInput))
			{	//�����
				if (wcscmp(m_LegAni->GetName(), _T("LEG_IDLE")) != 0)
					m_Leg_State = LEG_IDLE;
			}
			else
			{	//�ȴ� ���
				if (wcscmp(m_LegAni->GetName(), _T("LEG_RUN")) != 0)
					m_Leg_State = LEG_RUN;
			}
		}
		else
		{	//�������, ���⼺ �ִ� ���� ���
			if ((KEY_DOWN == m_DirKeyInput) || (KEY_DOWN_TO_LEFT == m_DirKeyInput)
				|| (KEY_DOWN_TO_RIGHT == m_DirKeyInput) || (KEY_IDLE == m_DirKeyInput))
			{	//������ ���� �Ǵ� �Ʒ�����ä�� ����
				if (wcscmp(m_LegAni->GetName(), _T("LEG_JUMP")) != 0)
					m_Leg_State = LEG_JUMP;
			}
			else
			{
				if (wcscmp(m_LegAni->GetName(), _T("LEG_DIRJUMP")) != 0)
					m_Leg_State = LEG_DIR_JUMP;
			}
		}
	}
	else
	{
	}
}

void CPlayer_1::LineCollision()
{
	float LineOnPosY_1 = NULL;
	float LineOnPosY_2 = NULL;
	LineOnPosPlayerY = NULL;
	float DistanceA = NULL;
	float DistanceB = NULL;
	SelectedLine = NULL;

	if (NULL != m_Line_List)
	{
		for (m_Line_Pos = m_Line_List->begin();
			m_Line_Pos != m_Line_List->end(); ++m_Line_Pos)
		{
			if (m_CenterPoint.getX() >= (*m_Line_Pos)->m_lPoint.x &&
				m_CenterPoint.getX() < (*m_Line_Pos)->m_rPoint.x)
			{	//�÷��̾ Ư�������� �ִ����� x��ǥ �񱳷� �Ǵ�. [1�� ��.]
				if (SelectedLine == NULL)
				{	//���Ǹ����ϴ� ���� 1�� Ȯ���� ��.
					SelectedLine = (*m_Line_Pos);
					LineOnPosPlayerY = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					LineOnPosY_1 = LineOnPosPlayerY;
				}
				else
				{	//�밡 �̻��� ���� ������ ������ ��. -> �� ���� �÷��̾� �� Ȥ�� �Ʒ��� ��ġ�� ����.
					//�÷��̾���� �Ÿ��� �� �� �Ǵ��Ѵ�.
					LineOnPosY_1 = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
						+ SelectedLine->m_lPoint.y;
					//������ �����ߴ� ������ Y��ǥ
					LineOnPosY_2 = (*m_Line_Pos)->m_Slope * (m_CenterPoint.getX() - (*m_Line_Pos)->m_lPoint.x)
						+ (*m_Line_Pos)->m_lPoint.y;
					DistanceA = abs(m_CenterPoint.getY() - LineOnPosY_1);
					DistanceB = abs(m_CenterPoint.getY() - LineOnPosY_2);

					if (DistanceB < DistanceA)
					{	//���� �˻��� ���� �� ����� ���
						SelectedLine = (*m_Line_Pos);
						LineOnPosPlayerY = SelectedLine->m_Slope * (m_CenterPoint.getX() - SelectedLine->m_lPoint.x)
							+ SelectedLine->m_lPoint.y;
						int temp = (int)LineOnPosPlayerY;
					}
					else
					{
						LineOnPosPlayerY = LineOnPosY_1;
					}
				}
			}
		}
		if (NULL != SelectedLine)
		{	//�� �˻��� ���� ��. �÷��̾ �� ������ ���������� �ϸ� ���ƾ� �Ѵ�.
			//�� �÷��̾ ������ �ؼ� ������ �հ��°��� ������ �ȵȴ�.
			if (m_CurLine == NULL)
				m_CurLine = SelectedLine;
			if (m_CurLine == SelectedLine)
			{
				if (m_Speed_Y >= 0)
				{
					if (m_CenterPoint.getY() >= LineOnPosPlayerY)
					{

						m_CenterPoint.setY(LineOnPosPlayerY);
						m_P_STATE = P_LAND;
					}
				}
				else
					m_P_STATE = P_JUMPING;
			}
			else
			{	//���� ����Ǿ��� ��.
				if (LineOnPosPlayerY > m_CenterPoint.getY())
				{	//���� �ִ� ������ ������ ��.
					m_P_STATE = P_LANDING;
				}
				else
				{	//�Ʒ��ִ� ������ �����ؼ� �ö� ��.
					m_P_STATE = P_JUMPING;
				}
				if (LineOnPosPlayerY + 20 > m_CenterPoint.getY() &&
					LineOnPosPlayerY - 30 < m_CenterPoint.getY())
					m_CurLine = SelectedLine;
			}
		}
	}
	else
	{
		return;
	}
}


void CPlayer_1::CheckCollision(CObj* _Something)
{	//�浹ü�� ���� �з��� ���ִ� ��.
	//�з��� ������ ����.
	//�Ϲ� ������[����/�Դ� ������] 
	// ����[����/��ũ] 
	// NPC 
	// �Ϲݿ�����Ʈ[�����ۻ���/���� ���] 
	// EnemyBullet[�Ѿ�/��ź]
	if (m_Body_State == BODY_KNIFE)
		m_Body_State = BODY_IDLE;
	if (m_Sit_State == SIT_KNIFE)
		m_Sit_State = SIT_IDLE;

	if (_Something->GetRTTI().isExactly(CW_Item::m_Rtti))
		CollisionWithWeaponItem(_Something);
	if (_Something->GetRTTI().isExactly(CN_Item::m_Rtti))
		CollisionWithNomalItem(_Something);
	if (_Something->GetRTTI().isExactly(CSoldier::m_Rtti))
		CollisionWithEnemy(_Something);
	if (_Something->GetRTTI().DerivesFrom(CNormalObj::m_Rtti))
		CollisionWithObject(_Something);
	if (isMuJeok == false)
	{
		if (_Something->GetRTTI().isExactly(CEnemyBullet::m_Rtti))
			CollisionWithEnemyWeapon(_Something);
	}
	//	CollisionWithEnemyWeapon(_Something);
	//if(_Something->GetRTTI().isExactly(CW_Item::m_Rtti))
	//	collisionWithObject(_Something);
}

void CPlayer_1::CollisionWithWeaponItem(CObj* _Something)
{

	if (wcscmp(((CW_Item*)_Something)->GetWeaponItemName(), _T("W_ITEM_H")) == 0)
	{
		if (m_Weapon != W_H)
			m_Parent->SetBulletCount(200);
		else
			m_Parent->AddBulletCount(100);
		m_Weapon = W_H;
	}
	if (wcscmp(((CW_Item*)_Something)->GetWeaponItemName(), _T("W_ITEM_F")) == 0)
	{
		if (m_Weapon != W_F)
			m_Parent->SetBulletCount(30);
		else
			m_Parent->AddBulletCount(15);
		m_Weapon = W_F;
	}
	if (wcscmp(((CW_Item*)_Something)->GetWeaponItemName(), _T("W_ITEM_S")) == 0)
	{
		if (m_Weapon != W_S)
			m_Parent->SetBulletCount(30);
		else
			m_Parent->AddBulletCount(15);
		m_Weapon = W_S;
	}
	if (wcscmp(((CW_Item*)_Something)->GetWeaponItemName(), _T("W_ITEM_RELOAD_BULLET")) == 0)
	{
		m_Parent->AddBulletCount(50);
	}
	if (wcscmp(((CW_Item*)_Something)->GetWeaponItemName(), _T("W_ITEM_RELOAD_BOMB")) == 0)
	{
		m_Parent->AddBomb(15);
	}
}
void CPlayer_1::CollisionWithObject(CObj* _Something)
{
	//�ϴ��� ���¸� �ٲ��� �� �ش� ������Ʈ�� ���հ� �Ѿ�� �ؾ��Ѵ�.

	RECT tempRect;

	m_Body_State = BODY_KNIFE;

	m_Sit_State = SIT_KNIFE;

	if (IntersectRect(&tempRect, &(_Something->GetRect()), &(GetRect())))
	{
		float L = float(tempRect.right - tempRect.left);
		float CenterL = float(tempRect.right + tempRect.left) / 2.f;
		float H = float(tempRect.bottom - tempRect.top);
		float CenterH = float(tempRect.bottom + tempRect.top) / 2.f;


		//�¿� �浹
		if (m_CenterPoint.getX() < CenterL)	//�÷��̾�� ������Ʈ�� ���ʿ� ����.
		{
			SetPos(m_CenterPoint.getX() - L, m_CenterPoint.getY());
		}
		else
		{
			SetPos(m_CenterPoint.getX() + L, m_CenterPoint.getY());
		}
	}
	if (IntersectRect(&tempRect, &(_Something->GetRect()), &(GetRect())))
	{
		float L = float(tempRect.right - tempRect.left);
		float CenterL = float(tempRect.right + tempRect.left) / 2.f;
		float H = float(tempRect.bottom - tempRect.top);
		float CenterH = float(tempRect.bottom + tempRect.top) / 2.f;

		if (m_CenterPoint.getY() < CenterL)	//�÷��̾�� ������Ʈ�� ���ʿ� ����.
		{
			SetPos(m_CenterPoint.getX(), m_CenterPoint.getY() - H);
		}
		else
		{
			SetPos(m_CenterPoint.getX(), m_CenterPoint.getY() + H);
		}
	}

}
void CPlayer_1::CollisionWithEnemy(CObj* _Something)
{	//���� ���� �� ������ �� ����. ��� ���˼����� ���⸦ ��� Į�� �ٲ�� ��.
	if (m_Stand_State == STAND_IDLE)
		m_Body_State = BODY_KNIFE;
	if (m_Stand_State == STAND_SIT)
		m_Sit_State = SIT_KNIFE;
	//�� ���α׷����� ���� �Ŀ��� ���¸� �ٽ� IDLE�̳� SIT���� �ٲ��ش�.
}
void CPlayer_1::CollisionWithNomalItem(CObj* _Something)
{	//���� ������ ���⼭.

}
void CPlayer_1::CollisionWithEnemyWeapon(CObj* _Something)
{

	if (_Something->GetRTTI().isExactly(CE_Bakgeok::m_Rtti))
	{
	}
	if (_Something->GetRTTI().isExactly(CE_BallingBomb::m_Rtti))
	{
	}
	if (_Something->GetRTTI().isExactly(CE_Bomb_1::m_Rtti))
	{
	}
	if (_Something->GetRTTI().isExactly(CE_Bomb_2::m_Rtti))
	{
	}
	if (_Something->GetRTTI().isExactly(CE_Mine::m_Rtti))
	{
	}
	if (_Something->GetRTTI().isExactly(CE_NomalBullet::m_Rtti))
	{
	}
	isDead = true;
}
void CPlayer_1::CollisionWithSlug(CObj* _Something)
{

}
