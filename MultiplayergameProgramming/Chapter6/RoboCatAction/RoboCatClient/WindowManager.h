#pragma once
class WindowManager
{
private:
	WindowManager(SDL_Window* _wnd);
	SDL_Window* mMainWindow;
public:
	static bool StaticInit();
	static unique_ptr<WindowManager> sInstance;
	~WindowManager();
public:

	SDL_Window* GetMainWindow() const
	{
		return mMainWindow;
	}
};

