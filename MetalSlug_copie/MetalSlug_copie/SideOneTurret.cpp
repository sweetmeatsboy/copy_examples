#include "stdafx.h"




const RTTI CSideOneTurret::m_Rtti("CSideOneTurret", CObj::m_Rtti);

void CSideOneTurret::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 100;
	m_tInfo.fCY = 100;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;

	m_TurretType = TurretType_MID;
	m_Turret_State = Turret_IDLE;
	m_TurretSFXAni = NULL;
	//초기 터렛타입이 MID이므로 2_IDLE을 지정해준다.
	m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_2_IDLE"));
	//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_2_IDLE"));
	m_Parent = NULL;
	m_Target = NULL;

	m_IdleDelay = 4000;
	m_TurningDelay = 3000;
	m_FiringDelay = 2000;
	m_dwPaternTimer = GetTickCount();

	isDead = false;
	m_dwFrameTimer = GetTickCount();

	CurFrame = 0;
	CurSFXFrame = 0;

	m_Posin_1.x = LONG(m_tInfo.fX);
	m_Posin_1.y = LONG(m_tInfo.fY - 10);

	m_PosinLength = 60;
	HP = 40.f;
}
void CSideOneTurret::ProgressIdle()
{
	if (GetTickCount() - m_dwFrameTimer > m_TurretAni->GetFrameDelay(CurFrame))
	{
		m_dwFrameTimer = GetTickCount();
		++CurFrame;
		if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
		{	//IDle로 있어야 하는 시간이 지난 후.
			m_dwPaternTimer = GetTickCount();
			m_Turret_State = Turret_TURNING;

			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_TURNING"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_SFX_0"));

			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_TURNING"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_SFX_0"));*/

		}
		if (CurFrame >= m_TurretAni->GetFrameCount())
			CurFrame = 0;
	}
}
void CSideOneTurret::ProgressTurning()
{
	CalcDistanceTarget();
	CurFrame = (int)m_TargetPosState;
	if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
	{	//IDle로 있어야 하는 시간이 지난 후.
		m_dwPaternTimer = GetTickCount();
		m_Turret_State = Turret_FIRING;
	}
}
void CSideOneTurret::ProgressFiring()
{	//Firing은 기존 Turning에서 SFX를 추가로 뿌리며 일정시간 조준하는 개념이다.
	CalcDistanceTarget();
	CurFrame = (int)m_TargetPosState;
	if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
	{	//IDle로 있어야 하는 시간이 지난 후.
		m_dwPaternTimer = GetTickCount();
		m_Turret_State = Turret_FIRE;
		CurFrame = 0;
		//ProgressFiring에ㅐ서 상태가 Fire로 바뀐 직후에 SFX를 띄워주며 탄도 생성해야 한다.
		//그리고 FIRE 애니메이션도 LEFT, MID, RIGHT를 여기서 정해줘야 함.


		if (m_TurretType == TurretType_MID)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_MID"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_SFX_2"));
			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_MID"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_SFX_2"));*/
		}
		if (m_TurretType == TurretType_LEFT)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_LEFT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_SFX_1"));
			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_LEFT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_SFX_1"));*/
		}
		if (m_TurretType == TurretType_RIGHT)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_RIGHT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_SFX_3"));
			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_RIGHT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_SFX_3"));*/
		}

		//탄을 여기서 생성한다.
		CObj* m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(1);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(2);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(3);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);
	}
}
void CSideOneTurret::ProgressFire()
{
	if (GetTickCount() - m_dwFrameTimer > m_TurretAni->GetFrameDelay(CurFrame))
	{
		m_dwFrameTimer = GetTickCount();
		++CurFrame;
		++CurSFXFrame;
		if (m_TurretSFXAni != NULL)
		{
			if (CurSFXFrame >= m_TurretSFXAni->GetFrameCount())
			{
				m_TurretSFXAni = NULL;
				CurSFXFrame = 0;
			}
		}

		if (CurFrame >= m_TurretAni->GetFrameCount())
		{	//발사 애니메이션이 끝난 후.
			m_dwPaternTimer = GetTickCount();
			m_Turret_State = Turret_TURNING;
			CalcDistanceTarget();
			CurFrame = (int)m_TargetPosState;
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_TURNING"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_ONE_TURRET_FIRING_SFX_0"));
			/*
						m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_TURNING"));
						m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_ONE_TURRET_FIRING_SFX_0"));*/
		}
	}
}

int CSideOneTurret::Progress(void)
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
		if (m_Turret_State == Turret_FIRING)
			ProgressFiring();
		if (m_Turret_State == Turret_FIRE)
			ProgressFire();
		return 0;
	}
}
void CSideOneTurret::Render(HDC _hdc)
{
	//Rectangle(_hdc, 
	//	int(m_tInfo.fX - m_tInfo.fCX/2.f),
	//	int(m_tInfo.fY - m_tInfo.fCY/2.f),
	//	int(m_tInfo.fX + m_tInfo.fCX/2.f),
	//	int(m_tInfo.fY + m_tInfo.fCY/2.f) );

	m_TurretAni->RenderAniSet(_hdc, CurFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
	if (m_TurretSFXAni != NULL)
	{
		if (m_Turret_State == Turret_FIRING || Turret_TURNING)
		{
			if (GetTickCount() % 6 != 0)
				m_TurretSFXAni->RenderAniSet(_hdc, CurSFXFrame, (float)m_SFX_1.x, (float)m_SFX_1.y, false);
		}
		else
			m_TurretSFXAni->RenderAniSet(_hdc, CurSFXFrame, (float)m_SFX_1.x, (float)m_SFX_1.y, false);
	}
	/*Ellipse(_hdc,
		int(m_CenterPoint.getX() - 3),
		int(m_CenterPoint.getY() - 3),
		int(m_CenterPoint.getX() + 3),
		int(m_CenterPoint.getY() + 3) );

	Rectangle(_hdc,
		int(m_SFX_1.x - 5),
		int(m_SFX_1.y - 5),
		int(m_SFX_1.x + 5),
		int(m_SFX_1.y + 5) );*/

}
void CSideOneTurret::Release(void)
{
}
void CSideOneTurret::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti))
	{
		HP -= ((CPlayerBullet*)_Something)->GetAtk();
		if (HP <= 0)
			isDead = true;
	}
}

void CSideOneTurret::UpdatePos()
{
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("sideOneTurret"), _T("SideOneTurret's Parent is NULL"), m_Parent == nullptr))
		return;

	m_tInfo.fX = m_Parent->GetInfo().fX + m_DeltaPos_X;
	m_tInfo.fY = m_Parent->GetInfo().fY + m_DeltaPos_Y;

	SetPos(m_Parent->GetInfo().fX + m_DeltaPos_X, m_Parent->GetInfo().fY + m_DeltaPos_Y);
}

void CSideOneTurret::SetTuerretState(TurretState _State)
{
	m_Turret_State = _State;
}
void CSideOneTurret::SetTuerretType(TurretType _Type)
{
	m_TurretType = _Type;
}
void CSideOneTurret::SetTarget(CObj* _Player)
{
	m_Target = _Player;
}
void CSideOneTurret::SetParent(CObj* _Parent)
{
	m_Parent = _Parent;
}
void CSideOneTurret::CalcDistanceTarget()
{
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("CSideTurret"), _T("UI_WeaponBox_Player is NULL"), m_Target == nullptr))
		return;
	int temp = abs(int(m_Target->GetInfo().fX - m_tInfo.fX));
	m_TargetPosState = Pos_None;
	if (m_Target->GetInfo().fX > m_tInfo.fX)
	{		//플레이어가 내 오른쪽에 있는 경우 [TargetPos : 1 ~ 5]
		if (temp >= 135)
		{

			m_SFX_1.x = int(m_CenterPoint.getX() + 10);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);

			m_TargetPosState = Pos_9;
		}
		if (temp < 135)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() + 7);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_8;
		}
		if (temp < 75)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() + 5);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_7;
		}
		if (temp < 45)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() + 2);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_6;
		}
		if (temp < 15)
		{
			m_SFX_1.x = int(m_CenterPoint.getX());
			m_SFX_1.y = int(m_CenterPoint.getY() - 8);
			m_TargetPosState = Pos_5;
		}
	}
	else
	{
		if (temp >= 135)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() - 10);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_1;
		}
		if (temp < 135)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() - 7);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_3;
		}
		if (temp < 75)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() - 5);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_3;
		}
		if (temp < 45)
		{
			m_SFX_1.x = int(m_CenterPoint.getX() - 2);
			m_SFX_1.y = int(m_CenterPoint.getY() - 15);
			m_TargetPosState = Pos_4;
		}
		if (temp < 15)
		{
			m_SFX_1.x = int(m_CenterPoint.getX());
			m_SFX_1.y = int(m_CenterPoint.getY() - 8);
			m_TargetPosState = Pos_5;
		}
	}
	if (m_TargetPosState >= Pos_1 && m_TargetPosState < Pos_4)
	{
		m_TurretType = TurretType_LEFT;
		m_fAngle = 135.f;
	}
	if (m_TargetPosState >= Pos_4 && m_TargetPosState < Pos_7)
	{
		m_TurretType = TurretType_MID;
		m_fAngle = 90.f;
	}
	if (m_TargetPosState >= Pos_7 && m_TargetPosState < Pos_None)
	{
		m_TurretType = TurretType_RIGHT;
		m_fAngle = 45.f;
	}
	m_Posin_1.x = int(m_CenterPoint.getX() + m_PosinLength * cosf(m_fAngle*PI / 180.f));
	m_Posin_1.y = int(m_CenterPoint.getY() - m_PosinLength * sinf(m_fAngle*PI / 180.f));


	if ((m_TargetPosState == Pos_1) || (m_TargetPosState == Pos_2))
		CurSFXFrame = 0;
	if ((m_TargetPosState == Pos_3))
		CurSFXFrame = 1;
	if ((m_TargetPosState == Pos_4))
		CurSFXFrame = 2;
	if ((m_TargetPosState == Pos_5))
		CurSFXFrame = 3;
	if ((m_TargetPosState == Pos_6))
		CurSFXFrame = 4;
	if ((m_TargetPosState == Pos_7))
		CurSFXFrame = 5;
	if ((m_TargetPosState == Pos_8) || (m_TargetPosState == Pos_9))
		CurSFXFrame = 6;

}
