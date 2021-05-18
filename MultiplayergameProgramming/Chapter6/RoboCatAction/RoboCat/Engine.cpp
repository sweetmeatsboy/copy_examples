#include "stdafx.h"

#include <time.h>
#include <SDL.h>

std::unique_ptr<Engine> Engine::sInstance;

Engine::Engine()
	: mShouldKeepRunning(true)
{
	SocketUtil::StaticInit();
	srand(static_cast<uint32_t>(time(nullptr)));
	GameObjectRegistry::StaticInit();

	World::StaticInit();
	ScoreBoardManager::Staticinit();

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

Engine::~Engine()
{
	SocketUtil::CleanUp();
	SDL_Quit();
}
int Engine::Run()
{
	return DoRunLoop();
}

void Engine::HandleEvent(SDL_Event* _e)
{
	;
}

int Engine::DoRunLoop()
{
	bool quit = false;
	SDL_Event e;
	memset(&e, 0, sizeof(SDL_Event));

	while (quit == false && mShouldKeepRunning)
	{
		if (SDL_PollEvent(&e))
		{
			if (SDL_PollEvent(&e))
			{
				if (e.type == SDL_QUIT)
					quit = true;
				else
					HandleEvent(&e);
			}
		}
		else
		{
			Timing::sInstance.Update();
			DoFrame();
		}
	}
	return e.type;
}


void Engine::DoFrame() 
{
	World::sInstance->Update();
}