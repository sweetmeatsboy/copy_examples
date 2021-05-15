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

	char m_TextContent[128];	// ������ �ؽ�Ʈ
	float m_TextBoxWidth;		// �ý�Ʈ �ڽ��� ũ�� ���� �� ���.
	float m_TextBoxHeight;	//�ؽ�Ʈ �ڽ��� ũ�� ���� �� ���.
	float m_TextBox_X;		//�ؽ�Ʈ �ڽ��� x��ǥ
	float m_TextBox_Y;		//�ؽ�Ʈ �ڽ��� y��ǥ

	float m_TextWidth;		//������ ���� ũ��
	float m_TextHeight;		//������ ���� ũ��

	TEXT_TYPE m_TextType;
	HDC m_MainDC;
	HDC m_TempDC;
	HBITMAP m_TemphBitmap;
public:
	void SetTextType(const char*);		//���ڿ� ������ �����ش�. 
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