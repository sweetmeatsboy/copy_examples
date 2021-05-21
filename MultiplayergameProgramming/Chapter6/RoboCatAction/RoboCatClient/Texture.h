#pragma once
class Texture
{
private:
	uint32_t mWidth;
	uint32_t mHeight;
	SDL_Texture* mTexture;
public:
	Texture(uint32_t _w, uint32_t _h, SDL_Texture* _t);
	~Texture();

	uint32_t GetWidth() const
	{
		return mWidth;
	}
	uint32_t GetHeight() const
	{
		return mHeight;
	}
	SDL_Texture* GetData() const
	{
		return mTexture;
	}
};

typedef shared_ptr<Texture> TexturePtr;

