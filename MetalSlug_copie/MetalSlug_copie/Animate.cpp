#include "stdafx.h"

CAnimate::CAnimate()
{}


CAnimate::~CAnimate()
{
	clearScenes();
}

CAnimate::CAnimate(const CAnimate& _other)
{
	vector<tagScene*>::const_iterator citer;
	for (citer = _other.m_vScenes.begin(); citer != _other.m_vScenes.end()
		; citer++)
	{
		addScene((*citer)->m_dwIndex, (*citer)->m_dwOutputTime);
	}
}

CAnimate& CAnimate::operator=(const  CAnimate& _other)
{
	if (&_other == this)
		return (*this);

	this->clearScenes();

	vector<tagScene*>::const_iterator citer;
	for (citer = _other.m_vScenes.begin(); citer != _other.m_vScenes.end();
		citer++)
	{
		addScene((*citer)->m_dwIndex, (*citer)->m_dwOutputTime);
	}
	return (*this);
}

void CAnimate::clearScenes()
{
	for (auto iter = m_vScenes.begin(); iter != m_vScenes.end(); iter++)
	{
		delete(*iter);
		(*iter) = nullptr;
	}
	m_vScenes.clear();
}

bool CAnimate::addScene(DWORD _idx, DWORD _time)
{
	tagScene* p = new tagScene();
	if (p == nullptr)
		return false;

	p->m_dwIndex = _idx;
	p->m_dwOutputTime = _time;
	m_vScenes.push_back(p);
	return true;
}

bool CAnimate::deleteScene(DWORD _idx)
{
	for (auto iter = m_vScenes.begin(); iter != m_vScenes.end(); iter++)
	{
		if ((*iter)->m_dwIndex != _idx)
			continue;
		delete (*iter);
		(*iter) = nullptr;
		m_vScenes.erase(iter);
		return true;
	}
	return false;
}


vector<CAnimate::tagScene*>::size_type CAnimate::getCntScene() const
{
	return m_vScenes.size();
}

const CAnimate::tagScene* CAnimate::getIdxOfScene(int _idx) const
{
	return m_vScenes.at(_idx);
}


bool CAnimate::changeTime(DWORD dwIndex, DWORD dwTime)
{
	std::vector<tagScene*>::iterator iter;

	bool bChange = false;

	for (iter = this->m_vScenes.begin(); iter != this->m_vScenes.end(); iter++)
	{
		if ((*iter)->m_dwIndex == dwIndex)
		{
			(*iter)->m_dwOutputTime = dwTime;
			bChange = true;
		}
	}

	return bChange;
}

void CAnimate::downIdx(DWORD dwIndex)
{
	std::vector<tagScene*>::iterator iter;

	for (iter = this->m_vScenes.begin(); iter != this->m_vScenes.end(); iter++)
	{
		if ((*iter)->m_dwIndex > dwIndex)
		{
			(*iter)->m_dwIndex--;
		}
	}
}