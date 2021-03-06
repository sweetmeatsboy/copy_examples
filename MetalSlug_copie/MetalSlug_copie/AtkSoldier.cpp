#include "stdafx.h"



const RTTI CAtkSoldier::m_Rtti("CAtkSoldier", CSoldier::m_Rtti);

void CAtkSoldier::SetAniName(const TCHAR* _Name)
{
	if (wcscmp(_Name, _T("AtkSoldier_29")) == 0)
	{
		m_AtkFrame = 6;
		m_ActType = STAND;
	}
	if (wcscmp(_Name, _T("AtkSoldier_30")) == 0)
	{
		m_AtkFrame = 8;
		m_ActType = STAND;
	}
	if (wcscmp(_Name, _T("AtkSoldier_32")) == 0)
	{
		m_AtkFrame = 9;
		m_ActType = SIT;
	}
	if (wcscmp(_Name, _T("AtkSoldier_33")) == 0)
	{
		m_AtkFrame = 7;
		m_ActType = STAND;
	}
	if (wcscmp(_Name, _T("AtkSoldier_34")) == 0)
	{
		m_AtkFrame = 3;
		m_ActType = SIT;
	}
	if (wcscmp(_Name, _T("AtkSoldier_35")) == 0)
	{
		m_AtkFrame = 9;
		m_ActType = STAND;
	}
	if (wcscmp(_Name, _T("AtkSoldier_36")) == 0)
	{
		m_AtkFrame = 9;
		m_ActType = STAND;
	}
	if (wcscmp(_Name, _T("AtkSoldier_38")) == 0)
	{
		m_AtkFrame = 9;
		m_ActType = SIT;
	}
	if (wcscmp(_Name, _T("AtkSoldier_40")) == 0)
	{
		m_AtkFrame = 9;
		m_ActType = JUMP;
	}
	if (wcscmp(_Name, _T("AtkSoldier_41")) == 0)
	{
		m_AtkFrame = 9;
		m_ActType = SIT;
	}
	if (wcscmp(_Name, _T("AtkSoldier_77")) == 0)
	{
		m_AtkFrame = 5;
		m_ActType = JUMP;
	}
	if (wcscmp(_Name, _T("AtkSoldier_48")) == 0)
	{
		m_AtkFrame = 1;
		m_ActType = SIT;
	}
	if (wcscmp(_Name, _T("AtkSoldier_42")) == 0)
	{
		m_AtkFrame = 1;
		m_ActType = STAND;
	}
	m_AtkSoldierAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Nomal_Soldier_AniSet"), _Name);
	//m_AtkSoldierAni = CAniInfoMgr::Getinst()->GetNormal_Soldier_AniSet(_Name);
	// 탄 클래스 설계 되면 탄 종류도 여기서 초기화 해주자.
}

void CAtkSoldier::SetParentSoldier(CSoldier* _Parent)
{
	m_Parent = _Parent;
}
void CAtkSoldier::LineCollision()
{
}
void CAtkSoldier::Initialize(void)
{
	SelectedLine = NULL;
	m_Line_List = NULL;
	///////////////////////
	//객체 기준 좌표 관련.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 15.f;
	m_Speed_Y = 0.f;

	memset(tempStr, 0, sizeof(tempStr));
	//객체 라인관련
	LineOnPosPlayerY = NULL;
	m_P_STATE = P_IDLE;
	PlayerIsMyLeft = false;
	//
	isDead = false;
	//애니메이션 관련 내용,.
	m_dwAniTimer = GetTickCount();
	CurFrame = 0;
	m_Parent = NULL;
}
int CAtkSoldier::Progress(void)
{
	if (m_Target->GetCenterPoint().getX() > m_Parent->GetCenterPoint().getX())
		PlayerIsMyLeft = false;
	else
		PlayerIsMyLeft = true;
	if (isDead == false)
	{
		SetPos(m_Parent->GetCenterPoint().getX(), m_Parent->GetCenterPoint().getY());
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_29")) == 0)	//수류탄
			Progress_AtkSoldier_29();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_30")) == 0)	//수류탄
			Progress_AtkSoldier_30();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_32")) == 0)	//수류탄
			Progress_AtkSoldier_32();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_33")) == 0)	//굴리는 폭탄
			Progress_AtkSoldier_33();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_34")) == 0)	//지뢰
			Progress_AtkSoldier_34();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_35")) == 0)	//폭죽
			Progress_AtkSoldier_35();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_36")) == 0)	//폭탄 2 던지는 놈.
			Progress_AtkSoldier_36();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_38")) == 0)	//박격포 쏘는 놈.
			Progress_AtkSoldier_38();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_40")) == 0)	//칼질하는 놈
			Progress_AtkSoldier_40();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_41")) == 0)	//칼질하는 놈
			Progress_AtkSoldier_41();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_77")) == 0)	//점프하면서 칼질하는 놈.
			Progress_AtkSoldier_77();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_48")) == 0)	//일반탄 쏘는 놈
			Progress_AtkSoldier_48();

		if (GetTickCount() - m_dwAniTimer > m_AtkSoldierAni->GetFrameInfoByIdx(CurFrame)->m_FrameTimer)
		{
			m_dwAniTimer = GetTickCount();
			if (CurFrame == m_AtkFrame)
			{
				FireToPlayer();
			}
			++CurFrame;
			if (CurFrame >= m_AtkSoldierAni->GetFrameCount())
			{
				CurFrame = 0;
			}
		}
		return 0;
	}
	else
		return 1;
}
void CAtkSoldier::Progress_AtkSoldier_29()//수류탄
{	//제자리 유지.
}
void CAtkSoldier::Progress_AtkSoldier_30()//수류탄
{	//제자리 유지.
}
void CAtkSoldier::Progress_AtkSoldier_32()//수류탄
{	//제자리 유지
}
void CAtkSoldier::Progress_AtkSoldier_33()//굴리는 폭탄
{	//제자리 유지
}
void CAtkSoldier::Progress_AtkSoldier_34()//지뢰
{	//플레이어 방향으로 살짝 도약해야됨.
	if (CurFrame == 1)
	{
		if (P_LAND == m_Parent->m_P_STATE)
		{
			m_Parent->SetSpeedY(-10.f);
			m_Parent->m_P_STATE = P_JUMPING;

		}
	}
	if (m_Parent->m_P_STATE == P_JUMPING || m_Parent->m_P_STATE == P_LANDING)
	{
		if (PlayerIsMyLeft == false)
			m_Parent->SetSpeedX(5.f);
		else
			m_Parent->SetSpeedX(-5.f);
	}
	else
		m_Parent->SetSpeedX(0.f);

}
void CAtkSoldier::Progress_AtkSoldier_35()//폭죽
{	//앞으로 약간 전진?
}
void CAtkSoldier::Progress_AtkSoldier_36()//폭탄 2 던지는 놈.
{	//제자리에서 던짐.
}
void CAtkSoldier::Progress_AtkSoldier_38()//박격포 쏘는 놈.
{	//제자리
}
void CAtkSoldier::Progress_AtkSoldier_40()//칼질하는 놈
{	//도약 후 칼질 및 찾지
	if (m_Parent->m_P_STATE == P_JUMPING || m_Parent->m_P_STATE == P_LANDING)
	{
		if (PlayerIsMyLeft == false)
			m_Parent->SetSpeedX(5.f);
		else
			m_Parent->SetSpeedX(-5.f);
	}
	else
		m_Parent->SetSpeedX(0.f);

	if (CurFrame == 1)
	{
		if (P_LAND == m_Parent->m_P_STATE)
		{
			m_Parent->SetSpeedY(-15.f);
			m_Parent->m_P_STATE = P_JUMPING;

		}
	}
}
void CAtkSoldier::Progress_AtkSoldier_41()//엎드려서 폭탄 2 투척하는 놈
{	//제자리 유지
}
void CAtkSoldier::Progress_AtkSoldier_48()//엎드려서 폭탄 2 투척하는 놈
{	//제자리 유지
}
void CAtkSoldier::Progress_AtkSoldier_77()//점프하면서 칼질하는 놈.
{	//도약 후 칼질 및 찾지.

	if (m_Parent->m_P_STATE == P_JUMPING || m_Parent->m_P_STATE == P_LANDING)
	{
		if (PlayerIsMyLeft == false)
			m_Parent->SetSpeedX(5.f);
		else
			m_Parent->SetSpeedX(-5.f);
	}
	else
		m_Parent->SetSpeedX(0.f);

	if (CurFrame == 1)
	{
		if (P_LAND == m_Parent->m_P_STATE)
		{
			m_Parent->SetSpeedY(-15.f);
			m_Parent->m_P_STATE = P_JUMPING;

		}
	}
}

void CAtkSoldier::Progress_AtkSoldier_42()
{
	PlayerIsMyLeft = !PlayerIsMyLeft;
}//칼질하는 놈
void CAtkSoldier::Render(HDC _hdc)
{
	m_AtkSoldierAni->RenderAniSet(_hdc, CurFrame,
		m_Parent->GetCenterPoint().getX(),
		m_Parent->GetCenterPoint().getY(), PlayerIsMyLeft);
}
void CAtkSoldier::Release(void)
{
}
void CAtkSoldier::FireToPlayer()
{
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_29")) == 0)	//수류탄
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_1, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_30")) == 0)	//수류탄
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_1, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_32")) == 0)	//수류탄
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_1, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_33")) == 0)	//굴리는 폭탄
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BALLING_BOMB, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_34")) == 0)	//지뢰
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_MINE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_35")) == 0)	//폭죽
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_FIREWORK, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_36")) == 0)	//폭탄 2 던지는 놈.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_2, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_38")) == 0)	//박격포 쏘는 놈.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BAKGEOK, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_40")) == 0)	//칼질하는 놈
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_KNIFE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_41")) == 0)	//칼질하는 놈
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_KNIFE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_77")) == 0)	//점프하면서 칼질하는 놈.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_KNIFE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_48")) == 0)	//점프하면서 칼질하는 놈.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_NOMAL, false);
}


void CAtkSoldier::CheckCollision(CObj* _Something)
{
	if (isDead == false)
	{
		srand(GetTickCount());

		if (_Something->GetRTTI().isExactly(CP_Knife::m_Rtti))
		{	//칼맞음
			int randNum = rand() % 4 + 1;
			m_Parent->isChildDead = true;
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_KNIFE, 0);
			if (m_ActType == SIT && isDead == false)
			{	//71
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_71"));
				isDead = true;
			}
			if (m_ActType == STAND && isDead == false)
			{	//57, 69, 70, 72 
				if (randNum == 1)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_57"));
				else if (randNum == 2)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_69"));
				else if (randNum == 3)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_70"));
				else
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_72"));

				isDead = true;
			}
			if (m_ActType == JUMP && isDead == false)
			{	//57, 69, 70, 72
				if (randNum == 1)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_57"));
				else if (randNum == 2)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_69"));
				else if (randNum == 3)
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_70"));
				else
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_72"));
				isDead = true;
			}
		}

		if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti))
		{
			m_Parent->isChildDead = true;
			int randNum = rand() % 3 + 1;
			//우선 플레이어 총알에 피격.
			if (_Something->GetRTTI().isExactly(CP_S::m_Rtti) && isDead == false)	//샷건
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_SHOTGUN, 0);
				if (m_ActType == SIT)
				{	// //67, 68
					if (randNum == 1)
					{
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_67"));
					}
					else
					{
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_68"));
					}
				}
				if (m_ActType == STAND)
				{	//28
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_28"));
				}
				if (m_ActType == JUMP)
				{	//28
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_28"));
				}
				isDead = true;
			}
			if ((_Something->GetRTTI().isExactly(CP_H::m_Rtti) || _Something->GetRTTI().isExactly(CP_NomalBullet::m_Rtti)) && isDead == false)	//머신건 또는 딱총.
			{
				if (m_ActType == SIT)
				{	//71
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_2, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_71"));
				}
				if (m_ActType == STAND)
				{	//30, 52, 53, 
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_3, 0);
					if (randNum == 1)
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_57"));
					else if (randNum == 2)
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_52"));
					else
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_53"));
				}
				if (m_ActType == JUMP)
				{	//58, 54
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_1, 0);
					if (randNum == 1)
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_58"));
					else if (randNum == 2)
						m_Parent->InsertDeadSoldier(_T("DeadSoldier_54"));
				}
				isDead = true;
			}
			if (_Something->GetRTTI().isExactly(CP_F::m_Rtti) && isDead == false)	//프레임샷
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_FIRE, 0);
				if (m_ActType == SIT)
				{	//100, 
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
				}
				if (m_ActType == STAND)
				{	//100
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_100"));
				}
				if (m_ActType == JUMP)
				{	//100
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_100"));
				}
				isDead = true;
			}
			if (_Something->GetRTTI().isExactly(CP_Bomb_1::m_Rtti) && isDead == false)	//프레임샷
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_FIRE, 0);
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
				isDead = true;
			}
		}

		if (_Something->GetRTTI().DerivesFrom(CExplosion::m_Rtti) && isDead == false)
		{	//폭발[스플레쉬]
			//폭발에서도 구분하자 -> 잠시 주석처리
			//m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
			//isDead = true;
		}
	}
}