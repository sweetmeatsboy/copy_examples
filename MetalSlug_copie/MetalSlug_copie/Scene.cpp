#include "stdafx.h"

CScene::CScene(const CRc& rcMain, const CPt& ptMain)
	: m_rcMain(rcMain), m_ptMain(ptMain)
{
}

CScene::~CScene()
{
	this->clearCollisionRect();
}

CScene::CScene(const CScene& rScene)
	: m_rcMain(rScene.m_rcMain), m_ptMain(rScene.m_ptMain)
{
	std::vector<CRc*>::const_iterator iter;

	for (iter = rScene.m_rcCollisions.begin()
		; iter != rScene.m_rcCollisions.end(); iter++)
	{
		this->m_rcCollisions.push_back(new CRc((*(*iter))));
	}
}

CScene& CScene::operator=(const CScene& rScene)
{
	if (this == &rScene)
		return (*this);

	this->m_rcMain = rScene.m_rcMain;
	this->m_ptMain = rScene.m_ptMain;

	this->clearCollisionRect();

	std::vector<CRc*>::const_iterator iter;

	for (iter = rScene.m_rcCollisions.begin()
		; iter != rScene.m_rcCollisions.end(); iter++)
	{
		this->m_rcCollisions.push_back(new CRc((*(*iter))));
	}

	return (*this);
}

const CRc& CScene::getMainRect() const
{
	return this->m_rcMain;
}

const CPt& CScene::getMainPoint() const
{
	return this->m_ptMain;
}

void CScene::setMainRect(CPt::PT_TYPE left, CPt::PT_TYPE up
	, CPt::PT_TYPE right, CPt::PT_TYPE down)
{
	this->m_rcMain.setLeft(left);
	this->m_rcMain.setUp(up);
	this->m_rcMain.setRight(right);
	this->m_rcMain.setDown(down);
}

void CScene::setMainRect(const CPt& rPoint1, const CPt& rPoint2)
{
	this->m_rcMain.setPoint1(rPoint1);
	this->m_rcMain.setPoint2(rPoint2);
}

void CScene::setMainRect(const CRc& rRc)
{
	this->m_rcMain = rRc;
}

void CScene::setMainPoint(CPt::PT_TYPE x, CPt::PT_TYPE y)
{
	this->m_ptMain.setX(x);
	this->m_ptMain.setY(y);
}

void CScene::setMainPoint(const CPt& rPoint)
{
	this->m_ptMain = rPoint;
}

void CScene::pushCollisionRect(const CRc& rRc)
{
	this->m_rcCollisions.push_back(new CRc(rRc));
}

const CRc* CScene::getCollisionRect(CPt::PT_TYPE x, CPt::PT_TYPE y) const
{
	std::vector<CRc*>::const_iterator iter;

	for (iter = this->m_rcCollisions.begin()
		; iter != this->m_rcCollisions.end(); iter++)
	{
		if ((*iter)->testInclusion(x, y))
			return (*iter);
	}

	return NULL;
}

const CRc* CScene::getCollisionRect(const CPt& rPoint) const
{
	return this->getCollisionRect(rPoint.getX(), rPoint.getY());
}

const CRc& CScene::getCollisionRect(int iIndex) const
{
	return (*this->m_rcCollisions.at(iIndex));
}

void CScene::deleteCollisionRect(const CRc& rRc)
{
	std::vector<CRc*>::iterator iter;

	for (iter = this->m_rcCollisions.begin()
		; iter != this->m_rcCollisions.end();)
	{
		if ((*(*iter)) == rRc)
		{
			iter = this->m_rcCollisions.erase(iter);
		}
		else
		{
			iter++;
		}
	}
}

void CScene::clearCollisionRect()
{
	std::vector<CRc*>::iterator iter;

	for (iter = this->m_rcCollisions.begin()
		; iter != this->m_rcCollisions.end(); iter++)
	{
		if ((*iter))
		{
			delete (*iter);
			(*iter) = 0;
		}
	}

	this->m_rcCollisions.clear();
}

bool CScene::testCollisionScene(const CPt& ptPos, const CScene& rScene, const CPt& ptPos2) const
{
	CRc rcTemp1;
	CRc rcTemp2;

	rcTemp1.setRight(ptPos.getX() + this->m_rcMain.getWidth() - this->m_ptMain.getX());
	rcTemp1.setDown(ptPos.getY() + this->m_rcMain.getHeight() - this->m_ptMain.getY());
	rcTemp1.setLeft(ptPos.getX() - this->m_ptMain.getX());
	rcTemp1.setUp(ptPos.getY() - this->m_ptMain.getY());

	rcTemp2.setRight(ptPos2.getX() + rScene.m_rcMain.getWidth() - rScene.m_ptMain.getX());
	rcTemp2.setDown(ptPos2.getY() + rScene.m_rcMain.getHeight() - rScene.m_ptMain.getY());
	rcTemp2.setLeft(ptPos2.getX() - rScene.m_ptMain.getX());
	rcTemp2.setUp(ptPos2.getY() - rScene.m_ptMain.getY());

	// 1Â÷ È®ÀÎ
	if (!rcTemp1.testCollision(rcTemp2))
		return false;

	std::vector<CRc*>::const_iterator iter;
	std::vector<CRc*>::size_type index = 0;
	std::vector<CRc*>::size_type count = rScene.getCountOfCollisionRect();

	if (count <= 0 || this->m_rcCollisions.size() <= 0)
		return true;

	for (iter = this->m_rcCollisions.begin()
		; iter != this->m_rcCollisions.end(); iter++)
	{
		rcTemp1 = CRc(0, 0, 0, 0);

		rcTemp1.setRight(ptPos.getX() + (*iter)->getRight() - this->m_ptMain.getX());
		rcTemp1.setDown(ptPos.getY() + (*iter)->getDown() - this->m_ptMain.getY());
		rcTemp1.setLeft(ptPos.getX() + (*iter)->getLeft() - this->m_ptMain.getX());
		rcTemp1.setUp(ptPos.getY() + (*iter)->getUp() - this->m_ptMain.getY());

		for (index = 0; index < count; index++)
		{

			rcTemp2 = CRc(0, 0, 0, 0);
			const CRc rcTemp3 = (rScene.getCollisionRect(index));
			rcTemp2.setRight(ptPos2.getX() + rcTemp3.getRight() - rScene.m_ptMain.getX());
			rcTemp2.setDown(ptPos2.getY() + rcTemp3.getDown() - rScene.m_ptMain.getY());
			rcTemp2.setLeft(ptPos2.getX() + rcTemp3.getLeft() - rScene.m_ptMain.getX());
			rcTemp2.setUp(ptPos2.getY() + rcTemp3.getUp() - rScene.m_ptMain.getY());

			if (rcTemp1.testCollision(rcTemp2))
				return true;
		}
	}

	return false;
}

std::vector<CRc*>::size_type CScene::getCountOfCollisionRect() const
{
	return this->m_rcCollisions.size();
}