#pragma once
class RenderManager
{
private:
	vector<SpriteComponent*> mComponents;
	SDL_Rect mViewTransform;
private:
	RenderManager();
public:
	static void StaticInit();
	static std::unique_ptr<RenderManager> sInstance;
public:
	void Render();
	void RenderComponents();

	void AddComponent(SpriteComponent* _comp);
	void RemoveComponent(SpriteComponent* _comp);
	int GetComponentIndex(SpriteComponent* _comp) const;
};

