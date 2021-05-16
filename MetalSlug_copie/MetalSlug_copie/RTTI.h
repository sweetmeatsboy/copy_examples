#pragma once

class RTTI
{
private:
	string m_ClassName;
	const RTTI* m_pBaseRTTI;
public:
	RTTI() : m_ClassName(""), m_pBaseRTTI(nullptr)
	{
	}
	RTTI(const string& _name)
		: m_ClassName(_name), m_pBaseRTTI(nullptr)
	{
	}
	RTTI(const string& _name, const RTTI& _parent)
		: m_ClassName(_name), m_pBaseRTTI(&_parent)
	{}
	~RTTI() {}
public:
	const string& ClassName() const;
	bool isExactly(const RTTI& _rtti) const;
	bool DerivesFrom(const RTTI& _rtti) const;
};