#include "RoboCatClientPCH.h"
#include "SDL_image.h"

unique_ptr<TextureManager> TextureManager::sInstance;

void TextureManager::StaticInit()
{
	sInstance.reset(new TextureManager());
}

TextureManager::TextureManager()
{
	CacheTexture("cat", "../Assets/cat.png");
	CacheTexture("mouse", "../Assets/mouse.png");
	CacheTexture("yarn", "../Assets/yarn.png");
}



TexturePtr TextureManager::GetTexture(const string& _name)
{
	return mNameToTextureMap[_name];
}

bool TextureManager::CacheTexture(string _name, const char* _fName)
{
	SDL_Texture* t = IMG_LoadTexture(GrahpicsDriver::sInstance->GetRenderer(), _fName);
	if (t == nullptr)
	{
		return false;
	}

	int w, h;

	SDL_QueryTexture(t, nullptr, nullptr, &w, &h);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	TexturePtr nT(new Texture(w, h, t));
	mNameToTextureMap[_name] = nT;
	return true;
}
