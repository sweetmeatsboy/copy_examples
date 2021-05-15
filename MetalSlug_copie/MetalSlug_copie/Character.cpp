#include "stdafx.h"

const RTTI CCharacter::m_Rtti("CCharacter", CObj::m_Rtti);

void CCharacter::GetGravity()
{
	if (P_LAND != m_P_STATE)
		m_Speed_Y += GRAVITY;
	else if (P_LAND == m_P_STATE)
		m_Speed_Y = 0.f;
}