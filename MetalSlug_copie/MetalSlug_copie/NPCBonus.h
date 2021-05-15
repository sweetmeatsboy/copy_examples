#pragma once

class CNPCBonus
{
private:
	CFrameDC* m_Icon;
	float m_Icon_Pos_X;
	float m_Icon_Pos_Y;

	float m_Icon_Size_Width;
	float m_Icon_Size_Height;
public:
	void SetIconPos(float _X, float _Y);
	void SetIconSize(float _W, float _H);
public:
	void Initialize();
	void Render(HDC _hdc);
public:
	CNPCBonus() {}
	~CNPCBonus() {}
};