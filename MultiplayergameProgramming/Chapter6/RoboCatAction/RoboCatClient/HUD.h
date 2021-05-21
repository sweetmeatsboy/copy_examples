#pragma once

#include "SDL_ttf.h"

class HUD
{
private:
	HUD();
private:
	Vector3 mBandWidthOrigin;
	Vector3 mRoundTripTimeOrigin;
	Vector3 mScoreBoardOrigin;
	Vector3 mScoreOffset;
	Vector3 mHealthOffset;
	SDL_Rect mViewTransform;

	TTF_Font* mFont;
	int mHealth;
private:
	void RenderBandWidth();
	void RenderRoundTripTime();
	void RenderScoreBoard();
	void RenderHealth();
	void RenderText(const string& _str, const Vector3& _orig, const Vector3& _color);
public:
	static void StaticInit();
	static unique_ptr<HUD> sInstance;

	void Render();
	void SetPlayerHealth(int _h)
	{
		mHealth = _h;
	}
};

