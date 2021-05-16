#include "stdafx.h"


const string& RTTI::ClassName() const
{
	return m_ClassName;
}

// A is Gameobject
bool RTTI::isExactly(const RTTI& _rtti) const
{
	return this == &_rtti;
}

// A as GameObject
bool RTTI::DerivesFrom(const RTTI& _rtti) const
{
	const RTTI* pCompare = this;
	while (pCompare != nullptr)
	{
		if (pCompare == &_rtti)
			return true;
		pCompare = pCompare->m_pBaseRTTI;
	}
	return false;
}