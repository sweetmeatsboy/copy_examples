#include "stdafx.h"

CPt::CPt(CPt::PT_TYPE _x, CPt::PT_TYPE _y)
	: m_x(_x), m_y(_y)
{
}

CPt::~CPt()
{
}
CPt::CPt(const CPt& _ref)
	: m_x(_ref.m_x), m_y(_ref.m_y)
{
}

CPt& CPt::operator=(const CPt& _ref)
{
	if (this == &_ref) // 자가대입 확인
		return (*this);

	this->m_x = _ref.m_x;
	this->m_y = _ref.m_y;
	return (*this);
}

bool CPt::operator==(const CPt& ref) const
{
	if (this->m_x == ref.m_x && this->m_y == ref.m_y)
		return true;
	else
		return false;
}

CPt::PT_TYPE CPt::getX() const 
{
	return this->m_x;
}

CPt::PT_TYPE CPt::getY() const
{
	return this->m_y;
}

void CPt::setX(CPt::PT_TYPE x)
{
	this->m_x = x;
}

void CPt::setY(CPt::PT_TYPE y)
{
	this->m_y = y;
}

double CPt::distance(const CPt &ref)
{
	return this->distance(ref.m_x, ref.m_y);
}

const CPt CPt::operator +(const CPt &ref) const
{
	return CPt(this->m_x + ref.m_x, this->m_y + ref.m_y);
}

const CPt CPt::operator -(const CPt &ref) const
{
	return CPt(this->m_x - ref.m_x, this->m_y - ref.m_y);
}

CPt& CPt::operator +=(const CPt &ref)
{
	this->m_x += ref.m_x;
	this->m_y += ref.m_y;
	return (*this);
}

CPt& CPt::operator -=(const CPt &ref)
{
	this->m_x -= ref.m_x;
	this->m_y -= ref.m_y;
	return (*this);
}

double CPt::distance(CPt::PT_TYPE x, CPt::PT_TYPE y)
{
	return sqrt(pow((static_cast<double>(x) - this->m_x), 2) + pow((static_cast<double>(y) - this->m_y), 2));
}


CPt CPt::getUnitVector()
{
	if (this->m_x == 0 && this->m_y == 0)
		return CPt(0, 0);

	float size = sqrt(pow(this->m_x, 2) + pow(this->m_y, 2));

	return CPt(this->m_x / size, this->m_y / size);
}