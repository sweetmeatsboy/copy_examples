#pragma once
class GraphicsDriver
{
private:
	GraphicsDriver();
	bool Init(SDL_Window* _wnd);

	SDL_Renderer* mRenderer;
	SDL_Rect mViewport;
public:
	static bool StaticInit(SDL_Window* _wnd);
	static unique_ptr<GraphicsDriver> sInstance;

	void Clear();
	void Present();
	SDL_Rect& GetLogicalViewport();
	SDL_Renderer* GetRenderer();
	~GraphicsDriver();
};

