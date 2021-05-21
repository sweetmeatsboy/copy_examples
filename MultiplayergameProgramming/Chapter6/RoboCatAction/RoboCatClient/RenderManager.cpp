#include "RoboCatClientPCH.h"

std::unique_ptr<RenderManager> RenderManager::sInstance;

RenderManager::RenderManager()
{
	SDL_Rect viewport = GraphicsDriver::sInstance->GetLogicalViewport();

	mViewTransform.x = viewport.w / 2;
	mViewTransform.y = viewport.h / 2;
	mViewTransform.w = 100;
	mViewTransform.h = 100;

}

void RenderManager::StaticInit()
{
	sInstance.reset(new RenderManager());
}

void RenderManager::AddComponent(SpriteComponent* _comp)
{
	mComponents.push_back(_comp);
}

void RenderManager::RemoveComponent(SpriteComponent* _comp)
{
	int idx = GetComponentIndex(_comp);
	if (idx == -1)
		return;
	int lastIdx = mComponents.size() - 1;
	if (idx != lastIdx)
		mComponents[idx] = mComponents[lastIdx];
	mComponents.pop_back();
}

int RenderManager::GetComponentIndex(SpriteComponent* _comp) const
{
	for (int idx = 0, c = mComponents.size(); idx < c; ++idx)
	{
		if (mComponents[idx] == _comp)
			return idx;
	}
	return -1;
}

void RenderManager::RenderComponents()
{
	SDL_Rect viewport = GraphicsDriver::sInstance
		->GetLogicalViewport();
	for (auto cit = mComponents.begin(), end = mComponents.end(); cit != end; cit++)
	{
		(*cit)->Draw(mViewTransform);
	}
}

void RenderManager::Render()
{
	GraphicsDriver::sInstance->Clear();
	RenderManager::sInstance->RenderComponents();

	HUD::sInstance->Render();
	
	GraphicsDriver::sInstance->Present();
}
