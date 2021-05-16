#pragma once

class CWeaponBox
{
private:
	CAniDCSet* TEST;
	CTextBox m_BulletCount;
	CTextBox m_BombCount;
	CPlayer* m_Player;

	CFrameDC* m_Bullet;
	CFrameDC* m_Canon;
	CFrameDC* m_Bomb;
	CFrameDC* m_OutLineBox;

	HDC m_MainDC;
	HDC m_TempDC;
	HBITMAP m_hBitmap;
private:
	float m_BoxPos_X;
	float m_BoxPos_Y;
	float m_Box_Width;
	float m_Box_Height;

	float m_Margin_X;
	float m_Margin_Y;

public:	//BoxUI 관련 조작 함수들
	void SetBoxPos(float _x, float _y);
	void SetBoxSize(float _x, float _y);
	void SetPlayer(CPlayer* _Player);
	void SetMarginX(float _MarginX);
	void SetMarginY(float _MarginY);
public:		//텍스트들 조작 함수들.
	void SetBulletCountSize(float _Width, float _Height);
	void SetBulletCountPos(float _x, float _y);
public:
	void SetBombCountSize(float _Width, float _Height);
	void SetBombCountPos(float _x, float _y);
public:
	float GetWeaponBox_X() const { return m_BoxPos_X; }
	float GetWeaponBox_Y() const { return m_BoxPos_Y; }
	float GetWeaponBox_Width() const { return m_Box_Width; }
	float GetWeaponBox_Height() const { return m_Box_Height; }
	CTextBox* GetBulletText() { return &m_BulletCount; }
	CTextBox* GetBombText() { return &m_BombCount; }
public:
	void Progress();
	void Initialize();
	void Render(HDC _hdc);
	void Release();
public:
	CWeaponBox() {}
	~CWeaponBox() {}
};