#include "RoboCatClientPCH.h"

unique_ptr<WindowManager> WindowManager::sInstance;

bool WindowManager::StaticInit()
{
	SDL_Window* wnd = SDL_CreateWindow("RobocatAct", 100, 100, 1280, 720
		, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (wnd == nullptr)
		return false;
	sInstance.reset(new WindowManager(wnd));
	return true;
}


WindowManager::WindowManager(SDL_Window* _wnd)
{
	mMainWindow = _wnd;
}

WindowManager::~WindowManager()
{
	SDL_DestroyWindow(mMainWindow);
}