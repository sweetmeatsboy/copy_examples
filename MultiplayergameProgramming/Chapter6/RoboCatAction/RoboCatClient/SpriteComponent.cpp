#include "RoboCatClientPCH.h"


SpriteComponent::SpriteComponent(GameObject* _obj)
	:mGameObject(_obj)
{
	float tWidth = 128.f;
	float tHeight = 128.f;

	mOrigin = Vector3(tWidth * 0.5f, tHeight *0.5f, 0.f);
	RendererManager::sinstance->AddComponent(this);
}

SpriteComponent::~SpriteComponent()
{
	RenderManager::sInstance->RemoveComponent(this);
}

void SpriteComponent::Draw(const SDL_Rect& _rect)
{
	if (mTexture == nullptr)
		return;

	Vector3 color = mGameObject->GetColor();
	Uint8 r= static_cast<Uint8>(color.x * 255);
	Uint8 g= static_cast<Uint8>(color.y * 255);
	Uint8 b= static_cast<Uint8>(color.z * 255);
	SDL_SetTextureColorMod(mTexture->GetData(), r, g, b);

	Vector3 loc = mGameObject->GetLocation();
	float scale = mGameObject->GetScale();

	SDL_Rect rect;
	rect.w = static_cast<int>(mTexture->GetWidth() * scale);
	rect.h = static_cast<int>(mTexture->GetHeight() * scale);
	rect.x = static_cast<int>(loc.x * _rect.w + _rect.x-rect.w / 2);
	rect.y = static_cast<int>(loc.y * _rect.h + _rect.y - rect.h / 2);

	SDL_RenderCopyEx(GraphicsDriver::sInstance->GetRenderer()
		, mTexture->GetData(), nullptr, &rect, RoboMath::ToDegrees(mGameObject->GetRotation()), nullptr, SDL_FLIP_NONE);
}