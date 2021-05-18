#pragma once
#include <SDL_events.h>
class Engine
{
private:
	bool mShouldKeepRunning;
	int DoRunLoop();
protected:
	Engine();
	virtual void DoFrame();
public:
	virtual ~Engine();
	static std::unique_ptr<Engine> sInstance;
	virtual int Run();
	void SetShouldKeppRunning(bool _flag)
	{
		mShouldKeepRunning = _flag;
	}
	virtual void HandleEvent(SDL_Event* _e);
};

