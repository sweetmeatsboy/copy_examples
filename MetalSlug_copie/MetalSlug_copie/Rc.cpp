#include "stdafx.h"

CRc::CRc(PTTYPE left, PTTYPE up, PTTYPE right, PTTYPE down)
	: m_point1(left, up), m_point2(right, down)
{
}

CRc::CRc(const CPt &rPoint1, const CPt &rPoint2)
	: m_point1(rPoint1), m_point2(rPoint2)
{
}

CRc::CRc()
	: m_point1(0, 0), m_point2(0, 0)
{
}

CRc::CRc(const CRc& rRc)
	: m_point1(rRc.m_point1), m_point2(rRc.m_point2)
{
}

CRc::~CRc()
{
}

CRc& CRc::operator=(const CRc& _other)
{
	if (this == &_other)
		return (*this);
	this->m_point1 = _other.m_point1;
	this->m_point2 = _other.m_point2;

	return (*this);
}

const CPt& CRc::getPoint1() const
{
	return this->m_point1;
}

const CPt& CRc::getPoint2() const
{
	return this->m_point2;
}

CPt::PT_TYPE CRc::getWidth() const
{
	return (this->m_point2.getX() - this->m_point1.getX());
}

CPt::PT_TYPE CRc::getHeight() const
{
	return (this->m_point2.getY() - this->m_point1.getY());
}

void CRc::Arrangement()
{
	if (this->m_point1.getX() > this->m_point2.getX())
	{
		CPt::PT_TYPE temp = this->m_point1.getX();
		this->m_point1.setX(this->m_point2.getX());
		this->m_point2.setX(temp);
	}

	if (this->m_point1.getY() > this->m_point2.getY())
	{
		CPt::PT_TYPE temp = this->m_point1.getY();
		this->m_point1.setY(this->m_point2.getY());
		this->m_point2.setY(temp);
	}
}

CPt::PT_TYPE CRc::getLeft() const
{
	return this->m_point1.getX();
}

CPt::PT_TYPE CRc::getUp() const
{
	return this->m_point1.getY();
}


CPt::PT_TYPE CRc::getRight() const
{
	return this->m_point2.getX();
}

CPt::PT_TYPE CRc::getDown() const
{
	return this->m_point2.getY();
}

CPt::PT_TYPE CRc::getArea() const
{
	return (this->getWidth() * this->getHeight());
}

bool CRc::testCollision(PTTYPE _l, PTTYPE _u, PTTYPE _r, PTTYPE _d) const
{
	return (this->m_point1.getX() <= _r && _l <= this->m_point2.getX()
		&& this->m_point1.getY() <= _d && _u <= this->m_point2.getY());
}

bool CRc::testCollision(const CPt& rPoint1, const CPt& rPoint2) const
{
	return this->testCollision(rPoint1.getX(), rPoint1.getY()
		, rPoint2.getX(), rPoint2.getY());
}

bool CRc::testCollision(const CRc &rRc) const
{
	return this->testCollision(rRc.getLeft(), rRc.getUp(), rRc.getRight(), rRc.getDown());
}

void CRc::setLeft(PTTYPE left)
{
	this->m_point1.setX(left);
	this->Arrangement();
}

void CRc::setUp(PTTYPE up)
{
	this->m_point1.setY(up);
	this->Arrangement();
}

void CRc::setRight(PTTYPE right)
{
	this->m_point2.setX(right);
	this->Arrangement();
}

void CRc::setDown(PTTYPE down)
{
	this->m_point2.setY(down);
	this->Arrangement();
}

void CRc::setPoint1(const CPt& rPoint)
{
	this->setLeft(rPoint.getX());
	this->setUp(rPoint.getY());
	this->Arrangement();
}

void CRc::setPoint2(const CPt& rPoint)
{
	this->setRight(rPoint.getX());
	this->setDown(rPoint.getY());
	this->Arrangement();
}

bool CRc::testInclusion(PTTYPE x, PTTYPE y) const
{
	return (x > this->m_point1.getX() && y > this->m_point1.getY()
		&& x < this->m_point2.getX() && y < this->m_point2.getY());
}

bool CRc::testInclusion(const CPt& rPoint) const
{
	return this->testInclusion(rPoint.getX(), rPoint.getY());
}

bool CRc::operator==(const CRc& rRc) const
{
	return (this->m_point1.getX() == rRc.m_point1.getX()
		&& this->m_point1.getY() == rRc.m_point1.getY()
		&& this->m_point2.getX() == rRc.m_point2.getX()
		&& this->m_point2.getY() == rRc.m_point2.getY());
}