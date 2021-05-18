#include "stdafx.h"


const RTTI CBigCanon::m_Rtti("CBigCanon", CObj::m_Rtti);

void CBigCanon::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 250;
	m_tInfo.fCY = 300;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;

	m_TurretType = TurretType_1;
	m_Turret_State = Turret_IDLE;

	
	//초기 터렛타입이 MID이므로 2_IDLE을 지정해준다.
	m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_APPERENCE"));
	//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_APPERENCE"));
	m_Parent = NULL;
	
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("Initialize"), _T("CBigCAnon is NULL"), CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->empty()) == false)
		m_Target = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();

	/*if (CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->empty() == false)
		m_Target = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();
	else
		MessageBox(g_hWnd, _T("Target is NULL"), _T("CBigCAnon"), MB_OK);*/

	m_IdleDelay = 2000;
	m_TurningDelay = 3000;
	m_FiringDelay = 2000;
	m_dwPaternTimer = GetTickCount();

	isDead = false;
	m_dwFrameTimer = GetTickCount();

	CurFrame = 0;
	m_PosinLength = 120;

	HP = 80.f;
}
void CBigCanon::ProgressIdle()
{
	if (GetTickCount() - m_dwFrameTimer > m_TurretAni->GetFrameDelay(CurFrame))
	{
		m_dwFrameTimer = GetTickCount();
		++CurFrame;
		if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
		{	//IDle로 있어야 하는 시간이 지난 후.
			m_dwPaternTimer = GetTickCount();
			m_Turret_State = Turret_TURNING;

			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_TARGETTING"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_TARGETTING"));
		}
		if (CurFrame >= m_TurretAni->GetFrameCount())
			CurFrame = m_TurretAni->GetFrameCount() - 1;
	}
}
void CBigCanon::ProgressTurning()
{
	CalcDistanceTarget();
	CurFrame = (int)m_TargetPosState;
	if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
	{	//IDle로 있어야 하는 시간이 지난 후.
		m_dwPaternTimer = GetTickCount();
		m_Turret_State = Turret_FIRE;
		CurFrame = 0;

		CObj* m_Bullet = CObjFactory<CBossBigBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);

		if (m_TurretType == TurretType_1)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_ANGLE_1"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_ANGLE_1"));
			((CBossBigBullet*)m_Bullet)->SetAniName(_T("BIG_CANON_BULLET_1"));
			((CBossBigBullet*)m_Bullet)->SetSpeedX(-7);
			((CBossBigBullet*)m_Bullet)->SetPlayerIsMyLeft(false);
		}
		if (m_TurretType == TurretType_2)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_ANGLE_2"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_ANGLE_2"));
			((CBossBigBullet*)m_Bullet)->SetAniName(_T("BIG_CANON_BULLET_3"));
			((CBossBigBullet*)m_Bullet)->SetSpeedX(-3);
			((CBossBigBullet*)m_Bullet)->SetPlayerIsMyLeft(false);
		}
		if (m_TurretType == TurretType_3)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_ANGLE_3"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_ANGLE_3"));
			((CBossBigBullet*)m_Bullet)->SetAniName(_T("BIG_CANON_BULLET_2"));
			((CBossBigBullet*)m_Bullet)->SetSpeedX(0);
			((CBossBigBullet*)m_Bullet)->SetPlayerIsMyLeft(true);
		}
		if (m_TurretType == TurretType_4)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_ANGLE_4"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_ANGLE_4"));
			((CBossBigBullet*)m_Bullet)->SetAniName(_T("BIG_CANON_BULLET_3"));
			((CBossBigBullet*)m_Bullet)->SetSpeedX(3);
			((CBossBigBullet*)m_Bullet)->SetPlayerIsMyLeft(true);
		}
		if (m_TurretType == TurretType_5)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_ANGLE_5"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_ANGLE_5"));
			((CBossBigBullet*)m_Bullet)->SetAniName(_T("BIG_CANON_BULLET_1"));
			((CBossBigBullet*)m_Bullet)->SetSpeedX(7);
			((CBossBigBullet*)m_Bullet)->SetPlayerIsMyLeft(true);
		}
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);
	}
}
void CBigCanon::ProgressFire()
{
	if (GetTickCount() - m_dwFrameTimer > m_TurretAni->GetFrameDelay(CurFrame))
	{
		m_dwFrameTimer = GetTickCount();
		++CurFrame;
		if (CurFrame >= m_TurretAni->GetFrameCount())
		{	//발사 애니메이션이 끝난 후.
			m_dwPaternTimer = GetTickCount();
			m_Turret_State = Turret_TURNING;
			CalcDistanceTarget();
			CurFrame = (int)m_TargetPosState;
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("BIG_CANON_TARGETTING"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BIG_CANON_TARGETTING"));
		}
	}
}

int CBigCanon::Progress(void)
{
	if (isDead == true)
		return 1;
	else
	{
		UpdatePos();
		if (m_Turret_State == Turret_IDLE)
			ProgressIdle();
		if (m_Turret_State == Turret_TURNING)
			ProgressTurning();
		if (m_Turret_State == Turret_FIRE)
			ProgressFire();
		return 0;
	}
}
void CBigCanon::Render(HDC _hdc)
{
	if (m_TurretAni != NULL)
		m_TurretAni->RenderAniSet(_hdc, CurFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
}
void CBigCanon::Release(void)
{
}
void CBigCanon::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti))
	{
		HP -= ((CPlayerBullet*)_Something)->GetAtk();
		if (HP <= 0)
			isDead = true;
	}
}

void CBigCanon::UpdatePos()
{
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("UpdatePos"), _T("BigCanon's Parent is NULL"), m_Parent == nullptr) == false)
		SetPos(m_Parent->GetInfo().fX + m_DeltaPos_X, m_Parent->GetInfo().fY + m_DeltaPos_Y);

	//if (m_Parent != NULL)
	//	SetPos(m_Parent->GetInfo().fX + m_DeltaPos_X, m_Parent->GetInfo().fY + m_DeltaPos_Y);
	//else
	//	MessageBox(g_hWnd, _T("BigCanon's Parent is NULL"), _T("Error"), MB_OK);
}
void CBigCanon::SetParent(CObj* _Parent)
{
	m_Parent = _Parent;
}
void CBigCanon::CalcDistanceTarget()
{
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("CalcDistanceTarget"), _T("CSideTurret is NULL"), m_Target != nullptr))
		return ;

	int temp = abs(int(m_Target->GetInfo().fX - m_tInfo.fX));
	m_TargetPosState = Pos_None;
	if (m_Target->GetInfo().fX > m_tInfo.fX)
	{		//플레이어가 내 오른쪽에 있는 경우 [TargetPos : 1 ~ 5]
		if (temp >= 135)
			m_TargetPosState = Pos_9;
		if (temp < 135)
			m_TargetPosState = Pos_8;
		if (temp < 75)
			m_TargetPosState = Pos_7;
		if (temp < 45)
			m_TargetPosState = Pos_6;
		if (temp < 15)
			m_TargetPosState = Pos_5;
	}
	else
	{
		if (temp >= 135)
			m_TargetPosState = Pos_1;
		if (temp < 135)
			m_TargetPosState = Pos_3;
		if (temp < 75)
			m_TargetPosState = Pos_3;
		if (temp < 45)
			m_TargetPosState = Pos_4;
		if (temp < 15)
			m_TargetPosState = Pos_5;
	}


	if (m_TargetPosState >= Pos_1 && m_TargetPosState < Pos_3)
	{
		m_TurretType = TurretType_1;
		m_fAngle = 135.f;
	}
	if (m_TargetPosState >= Pos_3 && m_TargetPosState < Pos_5)
	{
		m_TurretType = TurretType_2;
		m_fAngle = 110.f;
	}
	if (m_TargetPosState == Pos_5)
	{
		m_TurretType = TurretType_3;
		m_fAngle = 90.f;
	}
	if (m_TargetPosState >= Pos_6 && m_TargetPosState < Pos_8)
	{
		m_TurretType = TurretType_4;
		m_fAngle = 70.f;
	}
	if (m_TargetPosState >= Pos_8 && m_TargetPosState < Pos_None)
	{
		m_TurretType = TurretType_5;
		m_fAngle = 45.f;
	}

	m_Posin_1.x = int(m_CenterPoint.getX() + m_PosinLength * cosf(m_fAngle*PI / 180.f));
	m_Posin_1.y = int(m_CenterPoint.getY() - m_PosinLength * sinf(m_fAngle*PI / 180.f));
}
