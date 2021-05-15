#pragma once
class CFrameDC;

class CTextBox
{
private:
	enum TEXT_TYPE
	{
		TYPE_IDLE,
		BIG_SILVER,
		NOMAL_SILVER,
		SMALL_SILVER,
		BIG_GOLD,
		SMALL_GOLD
	};
private:
	map<char, CFrameDC*> m_Big_SilverSet;
	map<char, CFrameDC*> m_Nomal_SilverSet;
	map<char, CFrameDC*> m_Small_SilverSet;

	map<char, CFrameDC*> m_Big_GoldSet;
	map<char, CFrameDC*> m_Small_GoldSet;

	map<char, CFrameDC*>* m_CurAniSet;

	char m_TextContent[128];	// 보여줄 텍스트
	float m_TextBoxWidth;		// 택스트 박스의 크기 지정 시 사용.
	float m_TextBoxHeight;	//텍스트 박스의 크기 지정 시 사용.
	float m_TextBox_X;		//텍스트 박스의 x좌표
	float m_TextBox_Y;		//텍스트 박스의 y좌표

	float m_TextWidth;		//글자의 가로 크기
	float m_TextHeight;		//글자의 세로 크기

	TEXT_TYPE m_TextType;
	HDC m_MainDC;
	HDC m_TempDC;
	HBITMAP m_TemphBitmap;
public:
	void SetTextType(const char*);		//글자열 종류를 정해준다. 
	void SetText(char _text[]);
	void SetText(const char*);
	void SetText(int _Num);
	void SetTextBoxPos(float _x, float _y);
	void SetTextBoxSize(float _Width, float _Height);
public:
	void SoltingSmallSilver();
	void SoltingNomalSilver();
	void SoltingBigSilver();

	void SoltingSmallGold();
	void SoltingBigGold();
public:
	const char* GetText() const;
	float GetTextBoxX() const;
	float GetTextBoxY() const;
	float GetTextBoxWidth() const;
	float GetTextBoxHeight() const;
public:
	void Initialize();
	void Render(HDC _hdc);
public:
	CTextBox() {}
	~CTextBox() {}
};