#include "stdafx.h"


const RTTI CReactionSoldier::m_Rtti("CReactionSoldier", CSoldier::m_Rtti);

void CReactionSoldier::LineCollision()
{
}
void CReactionSoldier::Initialize(void)
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

int CReactionSoldier::Progress(void)
{
	if (isDead == true)
		return 1;
	if (m_Target != NULL)
	{
		if (GetTickCount() - m_dwAniTimer > m_ReactionSoldierAni->GetFrameInfoByIdx(CurFrame)->m_FrameTimer)
		{
			m_dwAniTimer = GetTickCount();
			++CurFrame;
			if (wcscmp(m_ReactionSoldierAni->GetName(), _T("Reaction_14")) == 0)
			{
				if (CurFrame >= m_ReactionSoldierAni->GetFrameCount())
					return 1;
			}
			else if (wcscmp(m_ReactionSoldierAni->GetName(), _T("Reaction_15")) == 0)
			{
				if (m_Target->GetInfo().fX > m_tInfo.fX)
					SetPos(m_Parent->GetCenterPoint().getX() - m_Speed_X,
						m_Parent->GetCenterPoint().getY() + m_Speed_Y);
				else
					SetPos(m_Parent->GetCenterPoint().getX() + m_Speed_X,
						m_Parent->GetCenterPoint().getY() + m_Speed_Y);
				if (CurFrame >= m_ReactionSoldierAni->GetFrameCount())
					return 1;
			}
		}
		return 0;
	}
	else
		return 1;
}
void CReactionSoldier::Render(HDC _hdc)
{
	if (wcscmp(m_ReactionSoldierAni->GetName(), _T("Reaction_14")) == 0)
	{
		if (m_Target->GetInfo().fX < m_tInfo.fX)
			m_ReactionSoldierAni->RenderAniSet(_hdc, CurFrame,
				m_Parent->GetCenterPoint().getX(),
				m_Parent->GetCenterPoint().getY(), false);
		else
			m_ReactionSoldierAni->RenderAniSet(_hdc, CurFrame,
				m_Parent->GetCenterPoint().getX(),
				m_Parent->GetCenterPoint().getY(), true);
	}
	if (wcscmp(m_ReactionSoldierAni->GetName(), _T("Reaction_15")) == 0)
	{
		if (m_Target->GetInfo().fX > m_tInfo.fX)
			m_ReactionSoldierAni->RenderAniSet(_hdc, CurFrame,
				m_Parent->GetCenterPoint().getX(),
				m_Parent->GetCenterPoint().getY(), true);
		else
			m_ReactionSoldierAni->RenderAniSet(_hdc, CurFrame,
				m_Parent->GetCenterPoint().getX(),
				m_Parent->GetCenterPoint().getY(), false);
	}

}
void CReactionSoldier::Release(void)
{
}
void CReactionSoldier::CheckCollision(CObj* _Something)
{
	/*
	#include "P_H.h"
	#include "P_S.h"
	#include "P_F.h"
	#include "P_Knife.h"
	#include "P_Bomb_1.h"
	#include "Explosion.h"
	*/
	if (isDead == false)
	{
		srand(GetTickCount());

		if (_Something->GetRTTI().isExactly(CP_Knife::m_Rtti) && isDead == false)
		{	//칼맞음
			m_Parent->isChildDead = true;
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_KNIFE, 0);
			int randNum = rand() % 4 + 1;
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

		if (_Something->GetRTTI().DerivesFrom(CPlayerBullet::m_Rtti) && isDead == false)
		{
			m_Parent->isChildDead = true;
			int randNum = rand() % 3 + 1;
			//우선 플레이어 총알에 피격.
			if (_Something->GetRTTI().isExactly(CP_S::m_Rtti) && isDead == false)	//샷건
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_SHOTGUN, 0);
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_28"));
				isDead = true;
			}
			if (_Something->GetRTTI().isExactly(CP_H::m_Rtti) || _Something->GetRTTI().isExactly(CP_NomalBullet::m_Rtti))	//머신건 또는 딱총.
			{
				if (randNum == 1)
				{
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_3, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_60"));
				}
				else if (randNum == 2)
				{
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_2, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_52"));
				}
				else
				{
					CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_BULLET_1, 0);
					m_Parent->InsertDeadSoldier(_T("DeadSoldier_53"));
				}
				isDead = true;
			}
			if (_Something->GetRTTI().isExactly(CP_F::m_Rtti) && isDead == false)	//프레임샷
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_FIRE, 0);
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_100"));
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
void CReactionSoldier::SetAniName(const TCHAR* _Name)
{
	m_ReactionSoldierAni = CAniInfoMgr::Getinst()->GetAniDCSet(_T("m_Nomal_Soldier_AniSet"), _Name);
	//m_ReactionSoldierAni = CAniInfoMgr::Getinst()->GetNormal_Soldier_AniSet(_Name);
	CurFrame = 0;
	MaxFrameCount = m_ReactionSoldierAni->GetFrameCount();
}

void CReactionSoldier::SetParentSoldier(CSoldier* _Parent)
{
	m_Parent = _Parent;
}