#include "RoboCatClientPCH.h"

Texture::Texture(uint32_t _w, uint32_t _h, SDL_Texture* _t)
	:mWidth(_w)
	, mHeight(_h)
	, mTexture(_t)
{
}

Texture::~Texture()
{
	SDL_DestroyTexture(mTexture);
}