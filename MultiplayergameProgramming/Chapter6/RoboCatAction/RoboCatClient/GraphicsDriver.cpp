#include "RoboCatClientPCH.h"

unique_ptr<GraphicsDriver> GraphicsDriver::sInstance;

namespace
{

}

bool GraphicsDriver::StaticInit(SDL_Window* _wnd)
{
	GraphicsDriver* nGD = new GraphicsDriver();
	bool ret = nGD->Init(_wnd);
	if (ret == false)
		delete nGD;
	else
		sInstance.reset(nGD);
	return ret;
}

bool GraphicsDriver::Init(SDL_Window* _wnd)
{
	mRenderer = SDL_CreateRenderer(_wnd, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, SDL_ALPHA_OPAQUE);
	SDL_RenderSetLogicalSize(mRenderer, 1280, 720);
	return true;
}

GraphicsDriver::GraphicsDriver()
	:mRenderer(nullptr)
{
}

GraphicsDriver::~GraphicsDriver()
{
	if (mRenderer == nullptr)
		return;
	SDL_DestroyRenderer(mRenderer);
}

void GraphicsDriver::Clear()
{
	SDL_RenderClear(mRenderer);
}

void GraphicsDriver::Present()
{
	SDL_RenderPresent(mRenderer);
}

SDL_Rect& GraphicsDriver::GetLogicalViewport()
{
	SDL_RenderGetLogicalSize(mRenderer, &mViewport.w, &mViewport.h);
	return mViewport;
}

SDL_Renderer* GraphicsDriver::GetRenderer()
{
	return mRenderer;
}