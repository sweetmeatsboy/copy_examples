#include "stdafx.h"

GameObject::GameObject()
	:mIndexInWorld(-1)
	, mCollisionRadius(0.5f)
	, mDoesWantToDie(false)
	, mRotation(0.f)
	, mNetworkId(0)
	, mColor(Colors::White)
	, mScale(1.0f)
{
}

void GameObject::Update()
{}

Vector3 GameObject::GetForwardVector() const
{
	return Vector3(sinf(mRotation), -cosf(mRotation), 0.f);
}

void GameObject::SetNetworkId(int _nid)
{
	mNetworkId = _nid;
}

void GameObject::SetRotation(float _val)
{
	mRotation = _val;
}

