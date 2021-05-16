#include "stdafx.h"


const RTTI CBoss::m_Rtti("CBoss", CObj::m_Rtti);

void CBoss::Initialize(void)
{
	//보스 자체의 속성값 설정 부분
	m_CenterPoint.setX(0);
	m_CenterPoint.setY(0);

	m_tInfo = INFO(WINCX / 2.f, WINCY / 2.f, 100.f, 100.f);

	m_tInfo.fCX = 600;
	m_tInfo.fCY = 450;

	m_tInfo.fX = m_CenterPoint.getX();
	m_tInfo.fY = m_CenterPoint.getY() - m_tInfo.fCY / 2.f;
	//객체 속성관련
	m_fAngle = 0.f;
	m_Speed_X = 5.f;
	m_Speed_Y = 0.f;

	m_BossPhase = PHASE_1;	//등장.

	m_PhaseTimer = GetTickCount();
	m_Phase1_Delay = 5000;
	m_Phase3_Delay = 500;
	m_Phase5_Delay = 6000;

	deltaShipHeadPosX = 0;

	Ship_Body.x = LONG(m_CenterPoint.getX() - 95);		//사령탑 부분,
	Ship_Body.y = LONG(m_CenterPoint.getY() - 110);
	Ship_Head.x = LONG(m_CenterPoint.getX() + deltaShipHeadPosX);	//선두
	Ship_Head.y = LONG(m_CenterPoint.getY());
	Ship_Tail.x = LONG(m_CenterPoint.getX() - 280);	//선미
	Ship_Tail.y = LONG(m_CenterPoint.getY() - 20);

	Wheel_F_Point.x = LONG(m_CenterPoint.getX() - 95);
	Wheel_F_Point.y = LONG(m_CenterPoint.getY());
	Wheel_B_Point.x = LONG(m_CenterPoint.getX() + 250);
	Wheel_B_Point.y = LONG(m_CenterPoint.getY());

	Radar_R_Point.x = LONG(m_CenterPoint.getX() - 90);
	Radar_R_Point.y = LONG(m_CenterPoint.getY() - 420);
	Radar_L_Point.x = LONG(m_CenterPoint.getX() + 32);
	Radar_L_Point.y = LONG(m_CenterPoint.getY() - 397);


	Turret_1_Broken = false;
	Turret_2_Broken = false;
	Turret_3_Broken = false;
	Turret_4_Broken = false;
	OneTurret_1_Broken = false;
	OneTurret_2_Broken = false;
	OneTurret_3_Broken = false;

	/////////////////////////////////////////


	//파츠들 초기화 부분.
	m_Side_Turret_1 = new CSideTurret();
	m_Side_Turret_2 = new CSideTurret();
	m_Side_Turret_3 = new CSideTurret();
	m_Side_Turret_4 = new CSideTurret();
	m_Side_One_Turret_1 = new CSideOneTurret();
	m_Side_One_Turret_2 = new CSideOneTurret();
	m_Side_One_Turret_3 = new CSideOneTurret();

	m_Target = CObjMgr::GetInst()->GetObjList(OBJ_PLAYER)->front();

	UpdateBrokenParstPoint();

	m_Side_Turret_1->Initialize();
	m_Side_Turret_2->Initialize();
	m_Side_Turret_3->Initialize();
	m_Side_Turret_4->Initialize();
	m_Side_One_Turret_1->Initialize();
	m_Side_One_Turret_2->Initialize();
	m_Side_One_Turret_3->Initialize();

	((CSideTurret*)m_Side_Turret_1)->SetDeltaPos(-163, -10);
	((CSideTurret*)m_Side_Turret_2)->SetDeltaPos(-133, -65);
	((CSideTurret*)m_Side_Turret_3)->SetDeltaPos(70, -100);
	((CSideTurret*)m_Side_Turret_4)->SetDeltaPos(105 + deltaShipHeadPosX, -65);
	((CSideOneTurret*)m_Side_One_Turret_1)->SetDeltaPos(-200, 65);
	((CSideOneTurret*)m_Side_One_Turret_2)->SetDeltaPos(-145, 75);
	((CSideOneTurret*)m_Side_One_Turret_3)->SetDeltaPos(-70, 45);



	((CSideTurret*)m_Side_Turret_1)->SetParent(this);
	((CSideTurret*)m_Side_Turret_2)->SetParent(this);
	((CSideTurret*)m_Side_Turret_3)->SetParent(this);
	((CSideTurret*)m_Side_Turret_4)->SetParent(this);
	((CSideOneTurret*)m_Side_One_Turret_1)->SetParent(this);
	((CSideOneTurret*)m_Side_One_Turret_2)->SetParent(this);
	((CSideOneTurret*)m_Side_One_Turret_3)->SetParent(this);

	((CSideTurret*)m_Side_Turret_1)->SetTarget(m_Target);
	((CSideTurret*)m_Side_Turret_2)->SetTarget(m_Target);
	((CSideTurret*)m_Side_Turret_3)->SetTarget(m_Target);
	((CSideTurret*)m_Side_Turret_4)->SetTarget(m_Target);
	((CSideOneTurret*)m_Side_One_Turret_1)->SetTarget(m_Target);
	((CSideOneTurret*)m_Side_One_Turret_2)->SetTarget(m_Target);
	((CSideOneTurret*)m_Side_One_Turret_3)->SetTarget(m_Target);

	((CSideTurret*)m_Side_Turret_1)->SetTuerretType(CSideTurret::TurretType_LEFT);
	((CSideTurret*)m_Side_Turret_2)->SetTuerretType(CSideTurret::TurretType_LEFT);
	((CSideTurret*)m_Side_Turret_3)->SetTuerretType(CSideTurret::TurretType_RIGHT);
	((CSideTurret*)m_Side_Turret_4)->SetTuerretType(CSideTurret::TurretType_RIGHT);
	((CSideOneTurret*)m_Side_One_Turret_1)->SetTuerretType(CSideOneTurret::TurretType_LEFT);
	((CSideOneTurret*)m_Side_One_Turret_2)->SetTuerretType(CSideOneTurret::TurretType_LEFT);
	((CSideOneTurret*)m_Side_One_Turret_3)->SetTuerretType(CSideOneTurret::TurretType_MID);


	m_PartsList.push_back(m_Side_Turret_1);
	m_PartsList.push_back(m_Side_Turret_2);
	m_PartsList.push_back(m_Side_Turret_3);
	m_PartsList.push_back(m_Side_Turret_4);
	m_PartsList.push_back(m_Side_One_Turret_1);
	m_PartsList.push_back(m_Side_One_Turret_2);
	m_PartsList.push_back(m_Side_One_Turret_3);
	//애니메이션 설정 부분.

	m_FrontWheelAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("WHELE_PARTS_FRONT"));
	m_BackWheelAni = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("WHELE_PARTS_BACK"));
	m_RightRadar = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("RADAR_PARTS_1"));
	m_LeftRadar = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("RADAR_PARTS_2"));

	m_BossHead = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BODY_PARTS"))->GetFrameInfoByIdx(0)->m_Frame;	//선미 부분
	m_BossBody = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BODY_PARTS"))->GetFrameInfoByIdx(14)->m_Frame;	//사령탑 부분
	m_BossTail = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BODY_PARTS"))->GetFrameInfoByIdx(6)->m_Frame;	//배기구 부분.

	m_Broken_Side_Turret_1 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Broken_Side_Turret_2 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(1)->m_Frame;
	m_Broken_Side_Turret_3 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(4)->m_Frame;
	m_Broken_Side_Turret_4 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(7)->m_Frame;
	m_Broken_Side_One_Turret_1 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(3)->m_Frame;
	m_Broken_Side_One_Turret_2 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(5)->m_Frame;
	m_Broken_Side_One_Turret_3 = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->GetFrameInfoByIdx(6)->m_Frame;

	//나머지  파츠들의 프레임관련 값들을 초기화해준다.
	m_RadarTimer_1 = GetTickCount();
	m_CurRadarFrame_1 = 0;
	m_RadarTimer_2 = GetTickCount();
	m_CurRadarFrame_2 = 0;

	m_FrontWheelTimer = GetTickCount();
	m_CurFrontWheelFrame = 0;
	m_BackWheelTimer = GetTickCount();
	m_CurBackWheelFrame = 0;

	roopNum = 0;
}
void CBoss::UpdateBrokenParstPoint()
{
	BrokenTurret_1.x = LONG(m_tInfo.fX - 163);
	BrokenTurret_1.y = LONG(m_tInfo.fY - 10);

	BrokenTurret_2.x = LONG(m_tInfo.fX - 133);
	BrokenTurret_2.y = LONG(m_tInfo.fY - 65);

	BrokenTurret_3.x = LONG(m_tInfo.fX + 70);
	BrokenTurret_3.y = LONG(m_tInfo.fY - 100);

	BrokenTurret_4.x = LONG(m_tInfo.fX + deltaShipHeadPosX + 105);
	BrokenTurret_4.y = LONG(m_tInfo.fY - 65);

	BrokenOneTurret_1.x = LONG(m_tInfo.fX - 200);
	BrokenOneTurret_1.y = LONG(m_tInfo.fY + 65);

	BrokenOneTurret_2.x = LONG(m_tInfo.fX - 145);
	BrokenOneTurret_2.y = LONG(m_tInfo.fY + 75);

	BrokenOneTurret_3.x = LONG(m_tInfo.fX - 70);
	BrokenOneTurret_3.y = LONG(m_tInfo.fY + 45);
}
void CBoss::AddBigCanon()
{
	//빅캐논은 변신부분에 넣어준다.
	m_BigCanon = new CBigCanon();
	m_BigCanon->Initialize();
	((CBigCanon*)m_BigCanon)->SetDeltaPos(153, -23);
	((CBigCanon*)m_BigCanon)->SetParent(this);

	if (Turret_3_Broken == true)
		m_PartsList.push_front(m_BigCanon);
	else
		m_PartsList.push_back(m_BigCanon);
}
void CBoss::ProgressPhase1()
{


	SetPos(m_CenterPoint.getX() + 2, m_CenterPoint.getY());
	if (GetTickCount() - m_PhaseTimer > m_Phase1_Delay)
	{
		m_BossPhase = PHASE_2;
	}
}
void CBoss::ProgressPhase2()
{

	srand(GetTickCount());

	int randDelta = rand() % 10 - 5;
	SetPos(m_CenterPoint.getX() + randDelta, m_CenterPoint.getY());
	if (m_PartsList.size() <= 3)
	{
		m_BossPhase = PHASE_3;
		m_PhaseTimer = GetTickCount();
	}
}
void CBoss::ProgressPhase3()
{

	deltaShipHeadPosX += 4;
	((CSideTurret*)m_Side_Turret_4)->SetDeltaPos(105 + deltaShipHeadPosX, -65);

	if (GetTickCount() - m_PhaseTimer > m_Phase3_Delay)
	{
		AddBigCanon();
		m_BossPhase = PHASE_4;
	}

}
void CBoss::ProgressPhase4()
{
	srand(GetTickCount());

	int randDelta = rand() % 10 - 5;
	SetPos(m_CenterPoint.getX() + randDelta, m_CenterPoint.getY());
	if (m_PartsList.size() == 0)
	{
		m_BossPhase = PHASE_5;
		m_PhaseTimer = GetTickCount();
		m_ExplossionTimer = GetTickCount();
	}
}
void CBoss::ProgressPhase5()
{
	int randDeltaX = rand() % 5 - 3;
	int randDeltaY = rand() % 2;
	SetPos(m_CenterPoint.getX() + randDeltaX, m_CenterPoint.getY() + randDeltaY);
	if (GetTickCount() - m_ExplossionTimer >= 600)
	{
		m_ExplossionTimer = GetTickCount();
		ExplosionGenerate();
	}
	if (GetTickCount() - m_PhaseTimer > m_Phase5_Delay)
	{
		m_BossPhase = PHASE_6;
	}
}
void CBoss::ExplosionGenerate()
{
	CExplosion* tempExplosion;
	srand(GetTickCount());

	int randNum = rand() % 3;
	if (randNum == 0)
	{
		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenTurret_1.x, (float)BrokenTurret_1.y);
		tempExplosion->SetExplosionName("Explosion_Middle");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);
		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenOneTurret_3.x, (float)BrokenOneTurret_3.y);
		tempExplosion->SetExplosionName("Explosion_Huge");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)Ship_Body.x, (float)Ship_Body.y);
		tempExplosion->SetExplosionName("Explosion_Max");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);
	}
	if (randNum == 1)
	{
		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)Ship_Tail.x, (float)Ship_Tail.y);
		tempExplosion->SetExplosionName("Explosion_Bomb_Max");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)Ship_Body.x, (float)Ship_Body.y);
		tempExplosion->SetExplosionName("Explosion_Max");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)Ship_Head.x, (float)Ship_Head.y);
		tempExplosion->SetExplosionName("Explosion_Mine_2");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)Wheel_F_Point.x, (float)Wheel_F_Point.y);
		tempExplosion->SetExplosionName("Explosion_Huge");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

	}
	if (randNum == 2)
	{
		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenOneTurret_3.x, (float)BrokenOneTurret_3.y);
		tempExplosion->SetExplosionName("Explosion_FireBomb");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenTurret_3.x, (float)BrokenTurret_3.y);
		tempExplosion->SetExplosionName("Explosion_Mine");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenTurret_2.x, (float)BrokenTurret_2.y);
		tempExplosion->SetExplosionName("Explosion_FireBomb_Finished");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenTurret_4.x, (float)BrokenTurret_4.y);
		tempExplosion->SetExplosionName("Explosion_Huge");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);

		tempExplosion = (CExplosion*)CObjFactory<CExplosion>::CreateObj((float)BrokenTurret_1.x, (float)BrokenTurret_1.y);
		tempExplosion->SetExplosionName("Explosion_Middle");
		CObjMgr::GetInst()->GetObjList(OBJ_EFFECT)->push_back(tempExplosion);
	}
}
int CBoss::Progress(void)
{
	if (m_BossPhase == PHASE_1)
		ProgressPhase1();
	if (m_BossPhase == PHASE_2)
		ProgressPhase2();
	if (m_BossPhase == PHASE_3)
		ProgressPhase3();
	if (m_BossPhase == PHASE_4)
		ProgressPhase4();
	if (m_BossPhase == PHASE_5)
		ProgressPhase5();

	if (m_PartsList.empty() == false)
	{
		for (m_PartsListPos = m_PartsList.begin();
			m_PartsListPos != m_PartsList.end(); )
		{
			if ((*m_PartsListPos)->Progress() == 1)
			{
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenTurret_1.x)
					Turret_1_Broken = true;
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenTurret_2.x)
					Turret_2_Broken = true;
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenTurret_3.x)
					Turret_3_Broken = true;
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenTurret_4.x)
					Turret_4_Broken = true;
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenOneTurret_1.x)
					OneTurret_1_Broken = true;
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenOneTurret_2.x)
					OneTurret_2_Broken = true;
				if ((*m_PartsListPos)->GetCenterPoint().getX() == BrokenOneTurret_3.x)
					OneTurret_3_Broken = true;

				delete (*m_PartsListPos);
				(*m_PartsListPos) = NULL;
				m_PartsListPos = m_PartsList.erase(m_PartsListPos);
			}
			else
				++m_PartsListPos;
		}
		//레이더 관련 부분.
		if (GetTickCount() - m_RadarTimer_1 > m_RightRadar->GetFrameDelay(m_CurRadarFrame_1))
		{	//오른쪽 레이더
			m_RadarTimer_1 = GetTickCount();
			++m_CurRadarFrame_1;
			if (m_CurRadarFrame_1 >= m_RightRadar->GetFrameCount())
				m_CurRadarFrame_1 = 0;
		}
		if (GetTickCount() - m_RadarTimer_2 > m_LeftRadar->GetFrameDelay(m_CurRadarFrame_2))
		{	//왼쪽 레이더.
			m_RadarTimer_2 = GetTickCount();
			++m_CurRadarFrame_2;
			if (m_CurRadarFrame_2 >= m_LeftRadar->GetFrameCount())
				m_CurRadarFrame_2 = 0;
		}
		//바퀴부분
		if (GetTickCount() - m_FrontWheelTimer > m_FrontWheelAni->GetFrameDelay(m_CurFrontWheelFrame))
		{	//오른쪽 레이더
			m_FrontWheelTimer = GetTickCount();
			++m_CurFrontWheelFrame;
			if (m_CurFrontWheelFrame >= m_FrontWheelAni->GetFrameCount())
				m_CurFrontWheelFrame = 0;
		}
		if (GetTickCount() - m_BackWheelTimer > m_BackWheelAni->GetFrameDelay(m_CurBackWheelFrame))
		{	//왼쪽 레이더.
			m_BackWheelTimer = GetTickCount();
			++m_CurBackWheelFrame;
			if (m_CurBackWheelFrame >= m_BackWheelAni->GetFrameCount())
				m_CurBackWheelFrame = 0;
		}
		return 0;
	}
	else
	{	// 모든 파츠가 부숴진 상태일 때.
		// 연출 및 폭파 애니메이션 보여줘야 한다.
		if (m_BossPhase == PHASE_6)
		{
			if (CDevice::GetInstance()->SoundPlaying(CDevice::BGM_BOSS) == true)
				CDevice::GetInstance()->SoundStop(CDevice::BGM_BOSS);
			CDevice::GetInstance()->SoundPlay(CDevice::SFX_SYS_MISSION_COMPLETE, 0);
			return 1;
		}
		else
			return 0;
	}
}

void CBoss::Render(HDC _hdc)
{
	UpdateBrokenParstPoint();

	/*Rectangle(_hdc,
		int(m_tInfo.fX - m_tInfo.fCX/2.f),
		int(m_tInfo.fY - m_tInfo.fCY/2.f),
		int(m_tInfo.fX + m_tInfo.fCX/2.f),
		int(m_tInfo.fY + m_tInfo.fCY/2.f) );*/
	if (m_BossPhase != PHASE_5)
	{
		if (m_PartsList.empty() == false)
		{
			RenderBody(_hdc);

			for (m_PartsListPos = m_PartsList.begin();
				m_PartsListPos != m_PartsList.end(); ++m_PartsListPos)
			{
				(*m_PartsListPos)->Render(_hdc);
			}
			RenderBrokenParts(_hdc);

			Ellipse(_hdc,
				Wheel_F_Point.x - 3, Wheel_F_Point.y - 3,
				Wheel_F_Point.x + 3, Wheel_F_Point.y + 3);

			Ellipse(_hdc,
				Wheel_B_Point.x - 3, Wheel_B_Point.y - 3,
				Wheel_B_Point.x + 3, Wheel_B_Point.y + 3);
			Ellipse(_hdc,
				Radar_R_Point.x - 3, Radar_R_Point.y - 3,
				Radar_R_Point.x + 3, Radar_R_Point.y + 3);
			Ellipse(_hdc,
				Radar_L_Point.x - 3, Radar_L_Point.y - 3,
				Radar_L_Point.x + 3, Radar_L_Point.y + 3);

			Ellipse(_hdc,
				Ship_Head.x - 3, Ship_Head.y - 3,
				Ship_Head.x + 3, Ship_Head.y + 3);
			Ellipse(_hdc,
				Ship_Body.x - 3, Ship_Body.y - 3,
				Ship_Body.x + 3, Ship_Body.y + 3);
			Ellipse(_hdc,
				Ship_Tail.x - 3, Ship_Tail.y - 3,
				Ship_Tail.x + 3, Ship_Tail.y + 3);

		}
		else
		{	//모든 파츠가 다 부서진 후.	// 연출 및 이팩트 관련된건 여기서...
		}
		//Ellipse(_hdc, 
		//	int(m_tInfo.fX - 3),
		//	int(m_tInfo.fY - 3),
		//	int(m_tInfo.fX + 3),
		//	int(m_tInfo.fY + 3) );
	}
	else
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("DEAD_BOSS"))->
			RenderAniSet(_hdc, 0, (float)m_CenterPoint.getX(), (float)m_CenterPoint.getY(), false);
	}
}

void CBoss::RenderBody(HDC _hdc)
{
	//레이더 부분
	Radar_R_Point.x = int(m_CenterPoint.getX() - 90);
	Radar_R_Point.y = int(m_CenterPoint.getY() - 420);
	Radar_L_Point.x = int(m_CenterPoint.getX() + 32);
	Radar_L_Point.y = int(m_CenterPoint.getY() - 397);

	//바디부분
	Ship_Body.x = LONG(m_CenterPoint.getX() - 95);		//사령탑 부분,
	Ship_Body.y = LONG(m_CenterPoint.getY() - 110);
	Ship_Head.x = LONG(m_CenterPoint.getX() + 110 + deltaShipHeadPosX);	//선두
	Ship_Head.y = LONG(m_CenterPoint.getY());
	Ship_Tail.x = LONG(m_CenterPoint.getX() - 280);	//선미
	Ship_Tail.y = LONG(m_CenterPoint.getY() - 20);

	//바퀴부분
	Wheel_F_Point.x = int(m_CenterPoint.getX() - 95);
	Wheel_F_Point.y = int(m_CenterPoint.getY());
	Wheel_B_Point.x = int(m_CenterPoint.getX() + 250);
	Wheel_B_Point.y = int(m_CenterPoint.getY());

	m_RightRadar->RenderAniSet(_hdc, m_CurRadarFrame_1, (float)Radar_R_Point.x, (float)Radar_R_Point.y, false);
	m_LeftRadar->RenderAniSet(_hdc, m_CurRadarFrame_2, (float)Radar_L_Point.x, (float)Radar_L_Point.y, false);
	//
	//m_BossHead = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet("BODY_PARTS")->GetFrameInfoByIdx(0)->m_Frame;	//선미 부분
	//m_BossBody = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet("BODY_PARTS")->GetFrameInfoByIdx(14)->m_Frame;	//사령탑 부분
	//m_BossTail = CAniInfoMgr::Getinst()->Get_Boss_1_AniSet("BODY_PARTS")->GetFrameInfoByIdx(6)->m_Frame;	//배기구 부분.

	m_BackWheelAni->RenderAniSet(_hdc, m_CurBackWheelFrame, (float)Wheel_B_Point.x, (float)Wheel_B_Point.y, false);

	CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BODY_PARTS"))->
		RenderAniSet(_hdc, 14, (float)Ship_Body.x, (float)Ship_Body.y, false);

	CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BODY_PARTS"))->
		RenderAniSet(_hdc, 0, (float)Ship_Head.x, (float)Ship_Head.y, false);

	CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BODY_PARTS"))->
		RenderAniSet(_hdc, 6, (float)Ship_Tail.x, (float)Ship_Tail.y, false);

	m_FrontWheelAni->RenderAniSet(_hdc, m_CurFrontWheelFrame, (float)Wheel_F_Point.x, (float)Wheel_F_Point.y, false);
}
void CBoss::RenderBrokenParts(HDC _hdc)
{
	if (Turret_1_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 2, (float)BrokenTurret_1.x, (float)BrokenTurret_1.y, false);
	}
	if (Turret_2_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 1, (float)BrokenTurret_2.x, (float)BrokenTurret_2.y, false);
	}
	if (Turret_3_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 4, (float)BrokenTurret_3.x, (float)BrokenTurret_3.y, false);
	}
	if (Turret_4_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 7, (float)BrokenTurret_4.x, (float)BrokenTurret_4.y, false);
	}
	if (OneTurret_1_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 3, (float)BrokenOneTurret_1.x, (float)BrokenOneTurret_1.y, false);
	}
	if (OneTurret_2_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 5, (float)BrokenOneTurret_2.x, (float)BrokenOneTurret_2.y, false);
	}
	if (OneTurret_3_Broken == true)
	{
		CAniInfoMgr::Getinst()->Get_Boss_1_AniSet(_T("BROKEN_BODY_PARTS"))->
			RenderAniSet(_hdc, 6, (float)BrokenOneTurret_3.x, (float)BrokenOneTurret_3.y, false);
	}
}

void CBoss::Release(void)
{
}

void CBoss::CheckCollision(CObj* _Something)
{
	RECT tempRect;
	if (m_PartsList.empty() == false)
	{
		for (m_PartsListPos = m_PartsList.begin();
			m_PartsListPos != m_PartsList.end(); ++m_PartsListPos)
		{
			if (IntersectRect(&tempRect, &(*m_PartsListPos)->GetRect(), &_Something->GetRect()))
			{
				(*m_PartsListPos)->CheckCollision(_Something);
			}
		}
	}
}