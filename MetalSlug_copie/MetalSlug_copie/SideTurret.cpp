#include "stdafx.h"



const RTTI CSideTurret::m_Rtti("CSideTurret", CObj::m_Rtti);

void CSideTurret::Initialize(void)
{
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 100;
	m_tInfo.fCY = 100;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//��ü �Ӽ�����
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;

	m_TurretType = TurretType_MID;
	m_Turret_State = Turret_IDLE;
	m_TurretSFXAni = NULL;
	//�ʱ� �ͷ�Ÿ���� MID�̹Ƿ� 2_IDLE�� �������ش�.
	m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_2_IDLE"));
	//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_2_IDLE"));
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

	m_DeltaPos_X = 0;
	m_DeltaPos_Y = 0;

	m_PosinLength = 60;

	HP = 35.f;
}
void CSideTurret::ProgressIdle()
{

	if (GetTickCount() - m_dwFrameTimer > m_TurretAni->GetFrameDelay(CurFrame))
	{
		m_dwFrameTimer = GetTickCount();
		++CurFrame;
		if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
		{	//IDle�� �־�� �ϴ� �ð��� ���� ��.
			m_dwPaternTimer = GetTickCount();
			m_Turret_State = Turret_TURNING;
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_TURNING"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_SFX_0"));

			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_TURNING"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_SFX_0"));*/

		}
		if (CurFrame >= m_TurretAni->GetFrameCount())
			CurFrame = 0;
	}
}
void CSideTurret::ProgressTurning()
{
	CalcDistanceTarget();
	CurFrame = (int)m_TargetPosState;
	if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
	{	//IDle�� �־�� �ϴ� �ð��� ���� ��.
		m_dwPaternTimer = GetTickCount();
		m_Turret_State = Turret_FIRING;
	}
}
void CSideTurret::ProgressFiring()
{	//Firing�� ���� Turning���� SFX�� �߰��� �Ѹ��� �����ð� �����ϴ� �����̴�.
	CalcDistanceTarget();
	CurFrame = (int)m_TargetPosState;
	if (GetTickCount() - m_dwPaternTimer > m_IdleDelay)
	{	//IDle�� �־�� �ϴ� �ð��� ���� ��.
		m_dwPaternTimer = GetTickCount();
		m_Turret_State = Turret_FIRE;
		CurFrame = 0;
		//ProgressFiring������ ���°� Fire�� �ٲ� ���Ŀ� SFX�� ����ָ� ź�� �����ؾ� �Ѵ�.
		//�׸��� FIRE �ִϸ��̼ǵ� LEFT, MID, RIGHT�� ���⼭ ������� ��.

		if (m_TurretType == TurretType_MID)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_MID"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_SFX_2"));
			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_MID"));
			//m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_SFX_2"));
		}
		if (m_TurretType == TurretType_LEFT)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_LEFT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_SFX_1"));
			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_LEFT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_SFX_1"));*/
		}
		if (m_TurretType == TurretType_RIGHT)
		{
			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_RIGHT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_SFX_3"));
			/*m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_RIGHT"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_SFX_3"));*/
		}
		CObj* m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(1);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(2);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_1.x, (float)m_Posin_1.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(3);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_2.x, (float)m_Posin_2.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(1);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_2.x, (float)m_Posin_2.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(2);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);

		m_Bullet = CObjFactory<CBossNomalBullet>::CreateObj((float)m_Posin_2.x, (float)m_Posin_2.y);
		((CBossNomalBullet*)m_Bullet)->SetBulletType(3);
		CObjMgr::GetInst()->GetObjList(OBJ_E_BULLET)->push_back(m_Bullet);
	}
}
void CSideTurret::ProgressFire()
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
		{	//�߻� �ִϸ��̼��� ���� ��.
			m_dwPaternTimer = GetTickCount();
			m_Turret_State = Turret_TURNING;
			CalcDistanceTarget();
			CurFrame = (int)m_TargetPosState;

			m_TurretAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_TURNING"));
			m_TurretSFXAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Boss_1_AniSet"), _T("SIDE_TURRET_FIRING_SFX_0"));

			//m_TurretAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_TURNING"));
			//m_TurretSFXAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("SIDE_TURRET_FIRING_SFX_0"));
		}
	}
}

int CSideTurret::Progress(void)
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
void CSideTurret::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
	int(m_tInfo.fX - m_tInfo.fCX/2.f),
	int(m_tInfo.fY - m_tInfo.fCY/2.f),
	int(m_tInfo.fX + m_tInfo.fCX/2.f),
	int(m_tInfo.fY + m_tInfo.fCY/2.f) );*/

	m_TurretAni->RenderAniSet(_hdc, CurFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
	if (m_TurretSFXAni != NULL)
	{
		if (m_Turret_State == Turret_FIRING || Turret_TURNING)
		{
			if (GetTickCount() % 6 != 0)
				m_TurretSFXAni->RenderAniSet(_hdc, CurSFXFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
		}
		else
			m_TurretSFXAni->RenderAniSet(_hdc, CurSFXFrame, m_CenterPoint.getX(), m_CenterPoint.getY(), false);
	}
	/*Ellipse(_hdc,
		int(m_CenterPoint.getX() - 3),
		int(m_CenterPoint.getY() - 3),
		int(m_CenterPoint.getX() + 3),
		int(m_CenterPoint.getY() + 3) );*/
		//Rectangle(_hdc, 
		//	int(m_Posin_1.x - 5),
		//	int(m_Posin_1.y - 5),
		//	int(m_Posin_1.x + 5),
		//	int(m_Posin_1.y + 5) );
		//Rectangle(_hdc, 
		//	int(m_Posin_2.x - 5),
		//	int(m_Posin_2.y - 5),
		//	int(m_Posin_2.x + 5),
		//	int(m_Posin_2.y + 5) );
}
void CSideTurret::Release(void)
{
}
void CSideTurret::CheckCollision(CObj* _Something)
{
	if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti))
	{
		HP -= ((CPlayerBullet*)_Something)->GetAtk();
		if (HP <= 0)
			isDead = true;
	}
}

void CSideTurret::UpdatePos()
{
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("sideOneTurret"), _T("SideOneTurret's Parent is NULL"), m_Parent == nullptr))
		return;

	SetPos(m_Parent->GetInfo().fX + m_DeltaPos_X, m_Parent->GetInfo().fY + m_DeltaPos_Y);
}

void CSideTurret::SetTuerretState(TurretState _State)
{
	m_Turret_State = _State;
}
void CSideTurret::SetTuerretType(TurretType _Type)
{
	m_TurretType = _Type;
}
void CSideTurret::SetTarget(CObj* _Player)
{
	m_Target = _Player;
}
void CSideTurret::SetParent(CObj* _Parent)
{
	m_Parent = _Parent;
}
void CSideTurret::CalcDistanceTarget()
{
	if (ErrorMgr::GetInst().ErrBoxPopupT(_T("sideTurret"), _T("Target is NULL"), m_Target == nullptr))
		return;
	int temp = abs(int(m_Target->GetInfo().fX - m_tInfo.fX));
	m_TargetPosState = Pos_None;
	if (m_Target->GetInfo().fX > m_tInfo.fX)
	{		//�÷��̾ �� �����ʿ� �ִ� ��� [TargetPos : 1 ~ 5]
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
	float TempAngle;
	if (m_TargetPosState >= Pos_1 && m_TargetPosState < Pos_4)
	{
		m_TurretType = TurretType_LEFT;
		m_fAngle = 120.f;
		TempAngle = 135.f;
	}
	if (m_TargetPosState >= Pos_4 && m_TargetPosState < Pos_7)
	{
		m_TurretType = TurretType_MID;
		m_fAngle = 95.f;
		TempAngle = 85.f;
	}
	if (m_TargetPosState >= Pos_7 && m_TargetPosState < Pos_None)
	{
		m_TurretType = TurretType_RIGHT;
		m_fAngle = 50.f;
		TempAngle = 65.f;
	}
	m_Posin_1.x = int(m_tInfo.fX + m_PosinLength * cosf(m_fAngle*PI / 180.f));
	m_Posin_1.y = int(m_tInfo.fY - m_PosinLength * sinf(m_fAngle*PI / 180.f));

	m_Posin_2.x = int(m_tInfo.fX + m_PosinLength * cosf(TempAngle*PI / 180.f));
	m_Posin_2.y = int(m_tInfo.fY - m_PosinLength * sinf(TempAngle*PI / 180.f));

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
