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
	// Åº Å¬·¡½º ¼³°è µÇ¸é Åº Á¾·ùµµ ¿©±â¼­ ÃÊ±âÈ­ ÇØÁÖÀÚ.
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
	//°´Ã¼ ±âÁØ ÁÂÇ¥ °ü·Ã.
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 80;
	m_tInfo.fCY = 80;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//°´Ã¼ ¼Ó¼º°ü·Ã
	m_fAngle = 0.f;
	m_Speed_X = 15.f;
	m_Speed_Y = 0.f;

	memset(tempStr, 0, sizeof(tempStr));
	//°´Ã¼ ¶óÀÎ°ü·Ã
	LineOnPosPlayerY = NULL;
	m_P_STATE = P_IDLE;
	PlayerIsMyLeft = false;
	//
	isDead = false;
	//¾Ö´Ï¸ÞÀÌ¼Ç °ü·Ã ³»¿ë,.
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
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_29")) == 0)	//¼ö·ùÅº
			Progress_AtkSoldier_29();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_30")) == 0)	//¼ö·ùÅº
			Progress_AtkSoldier_30();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_32")) == 0)	//¼ö·ùÅº
			Progress_AtkSoldier_32();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_33")) == 0)	//±¼¸®´Â ÆøÅº
			Progress_AtkSoldier_33();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_34")) == 0)	//Áö·Ú
			Progress_AtkSoldier_34();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_35")) == 0)	//ÆøÁ×
			Progress_AtkSoldier_35();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_36")) == 0)	//ÆøÅº 2 ´øÁö´Â ³ð.
			Progress_AtkSoldier_36();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_38")) == 0)	//¹Ú°ÝÆ÷ ½î´Â ³ð.
			Progress_AtkSoldier_38();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_40")) == 0)	//Ä®ÁúÇÏ´Â ³ð
			Progress_AtkSoldier_40();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_41")) == 0)	//Ä®ÁúÇÏ´Â ³ð
			Progress_AtkSoldier_41();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_77")) == 0)	//Á¡ÇÁÇÏ¸é¼­ Ä®ÁúÇÏ´Â ³ð.
			Progress_AtkSoldier_77();
		if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_48")) == 0)	//ÀÏ¹ÝÅº ½î´Â ³ð
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
void CAtkSoldier::Progress_AtkSoldier_29()//¼ö·ùÅº
{	//Á¦ÀÚ¸® À¯Áö.
}
void CAtkSoldier::Progress_AtkSoldier_30()//¼ö·ùÅº
{	//Á¦ÀÚ¸® À¯Áö.
}
void CAtkSoldier::Progress_AtkSoldier_32()//¼ö·ùÅº
{	//Á¦ÀÚ¸® À¯Áö
}
void CAtkSoldier::Progress_AtkSoldier_33()//±¼¸®´Â ÆøÅº
{	//Á¦ÀÚ¸® À¯Áö
}
void CAtkSoldier::Progress_AtkSoldier_34()//Áö·Ú
{	//ÇÃ·¹ÀÌ¾î ¹æÇâÀ¸·Î »ìÂ¦ µµ¾àÇØ¾ßµÊ.
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
void CAtkSoldier::Progress_AtkSoldier_35()//ÆøÁ×
{	//¾ÕÀ¸·Î ¾à°£ ÀüÁø?
}
void CAtkSoldier::Progress_AtkSoldier_36()//ÆøÅº 2 ´øÁö´Â ³ð.
{	//Á¦ÀÚ¸®¿¡¼­ ´øÁü.
}
void CAtkSoldier::Progress_AtkSoldier_38()//¹Ú°ÝÆ÷ ½î´Â ³ð.
{	//Á¦ÀÚ¸®
}
void CAtkSoldier::Progress_AtkSoldier_40()//Ä®ÁúÇÏ´Â ³ð
{	//µµ¾à ÈÄ Ä®Áú ¹× Ã£Áö
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
void CAtkSoldier::Progress_AtkSoldier_41()//¾þµå·Á¼­ ÆøÅº 2 ÅõÃ´ÇÏ´Â ³ð
{	//Á¦ÀÚ¸® À¯Áö
}
void CAtkSoldier::Progress_AtkSoldier_48()//¾þµå·Á¼­ ÆøÅº 2 ÅõÃ´ÇÏ´Â ³ð
{	//Á¦ÀÚ¸® À¯Áö
}
void CAtkSoldier::Progress_AtkSoldier_77()//Á¡ÇÁÇÏ¸é¼­ Ä®ÁúÇÏ´Â ³ð.
{	//µµ¾à ÈÄ Ä®Áú ¹× Ã£Áö.

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
}//Ä®ÁúÇÏ´Â ³ð
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
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_29")) == 0)	//¼ö·ùÅº
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_1, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_30")) == 0)	//¼ö·ùÅº
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_1, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_32")) == 0)	//¼ö·ùÅº
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_1, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_33")) == 0)	//±¼¸®´Â ÆøÅº
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BALLING_BOMB, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_34")) == 0)	//Áö·Ú
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_MINE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_35")) == 0)	//ÆøÁ×
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_FIREWORK, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_36")) == 0)	//ÆøÅº 2 ´øÁö´Â ³ð.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BOMB_2, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_38")) == 0)	//¹Ú°ÝÆ÷ ½î´Â ³ð.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_BAKGEOK, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_40")) == 0)	//Ä®ÁúÇÏ´Â ³ð
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_KNIFE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_41")) == 0)	//Ä®ÁúÇÏ´Â ³ð
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_KNIFE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_77")) == 0)	//Á¡ÇÁÇÏ¸é¼­ Ä®ÁúÇÏ´Â ³ð.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_KNIFE, false);
	if (wcscmp(m_AtkSoldierAni->GetName(), _T("AtkSoldier_48")) == 0)	//Á¡ÇÁÇÏ¸é¼­ Ä®ÁúÇÏ´Â ³ð.
		CBulletMgr::EnemyFire(m_tInfo.fX, m_tInfo.fY, m_fAngle, EW_NOMAL, false);
}


void CAtkSoldier::CheckCollision(CObj* _Something)
{
	if (isDead == false)
	{
		srand(GetTickCount());

		if (_Something->GetRTTI().isExactly(CP_Knife::m_Rtti))
		{	//Ä®¸ÂÀ½
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
			//¿ì¼± ÇÃ·¹ÀÌ¾î ÃÑ¾Ë¿¡ ÇÇ°Ý.
			if (_Something->GetRTTI().isExactly(CP_S::m_Rtti) && isDead == false)	//¼¦°Ç
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
			if ((_Something->GetRTTI().isExactly(CP_H::m_Rtti) || _Something->GetRTTI().isExactly(CP_NomalBullet::m_Rtti)) && isDead == false)	//¸Ó½Å°Ç ¶Ç´Â µüÃÑ.
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
			if (_Something->GetRTTI().isExactly(CP_F::m_Rtti) && isDead == false)	//ÇÁ·¹ÀÓ¼¦
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
			if (_Something->GetRTTI().isExactly(CP_Bomb_1::m_Rtti) && isDead == false)	//ÇÁ·¹ÀÓ¼¦
			{
				CDevice::GetInstance()->SoundPlay(CDevice::SFX_ENEMY_DEAD_FIRE, 0);
				m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
				isDead = true;
			}
		}

		if (_Something->GetRTTI().DerivesFrom(CExplosion::m_Rtti) && isDead == false)
		{	//Æø¹ß[½ºÇÃ·¹½¬]
			//Æø¹ß¿¡¼­µµ ±¸ºÐÇÏÀÚ -> Àá½Ã ÁÖ¼®Ã³¸®
			//m_Parent->InsertDeadSoldier(_T("DeadSoldier_59"));
			//isDead = true;
		}
	}
}