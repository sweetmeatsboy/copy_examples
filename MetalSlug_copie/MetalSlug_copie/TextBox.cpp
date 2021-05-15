#include "stdafx.h"


void CTextBox::SetTextType(const char* _Type)		//글자열 종류를 정해준다. 
{
	if (strcmp(_Type, "BIG_SILVER") == 0)
	{
		m_CurAniSet = &m_Big_SilverSet;
		m_TextType = BIG_SILVER;
	}
	if (strcmp(_Type, "NOMAL_SILVER") == 0)
	{
		m_CurAniSet = &m_Nomal_SilverSet;
		m_TextType = NOMAL_SILVER;
	}
	if (strcmp(_Type, "SMALL_SILVER") == 0)
	{
		m_CurAniSet = &m_Small_SilverSet;
		m_TextType = SMALL_SILVER;
	}
	if (strcmp(_Type, "BIG_GOLD") == 0)
	{
		m_CurAniSet = &m_Big_GoldSet;
		m_TextType = BIG_GOLD;
	}
	if (strcmp(_Type, "SMALL_GOLD") == 0)
	{
		m_CurAniSet = &m_Small_GoldSet;
		m_TextType = SMALL_GOLD;
	}
}
void CTextBox::SetText(char _Text[])
{
	memset(m_TextContent, 0, sizeof(m_TextContent));
	strcpy_s(m_TextContent, _Text);
}
void CTextBox::SetText(const char* _Text)
{
	memset(m_TextContent, 0, sizeof(m_TextContent));
	sprintf_s(m_TextContent, "%s", _Text);
}
void CTextBox::SetText(int _Num)
{
	memset(m_TextContent, 0, sizeof(m_TextContent));
	if (_Num < 0)	//탄약 무한대는 음수값을 넘겨받자.
	{
		sprintf_s(m_TextContent, "%c", 'N');
	}
	else
	{
		sprintf_s(m_TextContent, "%d", _Num);
	}
}
void CTextBox::SetTextBoxPos(float _x, float _y)
{
	m_TextBox_X = _x;
	m_TextBox_Y = _y;
}
void CTextBox::SetTextBoxSize(float _W, float _H)
{
	m_TextBoxWidth = _W;
	m_TextBoxHeight = _H;
}
const char* CTextBox::GetText() const
{
	return m_TextContent;
}
float CTextBox::GetTextBoxX() const
{
	return m_TextBox_X;
}
float CTextBox::GetTextBoxY() const
{
	return m_TextBox_Y;
}
float CTextBox::GetTextBoxWidth() const
{
	return m_TextBoxWidth;
}
float CTextBox::GetTextBoxHeight() const
{
	return m_TextBoxHeight;
}
void CTextBox::Initialize()
{
	memset(m_TextContent, 0, sizeof(m_TextContent));
	m_TextBoxWidth = 0.f;		// 택스트 박스의 크기 지정 시 사용.
	m_TextBoxHeight = 0.f;		//텍스트 박스의 크기 지정 시 사용.
	m_TextBox_X = 0.f;			//텍스트 박스의 x좌표
	m_TextBox_Y = 0.f;			//텍스트 박스의 y좌표

	m_TextWidth = 0.f;			//글자의 가로 크기
	m_TextHeight = 0.f;			//글자의 세로 크기

	m_TextType = TYPE_IDLE;
	m_CurAniSet = NULL;


	SoltingSmallSilver();
	SoltingNomalSilver();
	SoltingBigSilver();

	SoltingSmallGold();
	SoltingBigGold();

	m_MainDC = GetDC(g_hWnd);
	m_TempDC = CreateCompatibleDC(m_MainDC);
	m_TemphBitmap = CreateCompatibleBitmap(m_MainDC, WINCX, WINCY);
	SelectObject(m_TempDC, m_TemphBitmap);

	ReleaseDC(g_hWnd, m_MainDC);
	DeleteObject(m_TemphBitmap);
}
void CTextBox::SoltingSmallSilver()
{
	m_Small_SilverSet['0'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(0)->m_Frame;
	m_Small_SilverSet['1'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(1)->m_Frame;
	m_Small_SilverSet['2'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Small_SilverSet['3'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(3)->m_Frame;
	m_Small_SilverSet['4'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(4)->m_Frame;
	m_Small_SilverSet['5'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(5)->m_Frame;
	m_Small_SilverSet['6'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(6)->m_Frame;
	m_Small_SilverSet['7'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(7)->m_Frame;
	m_Small_SilverSet['8'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(8)->m_Frame;
	m_Small_SilverSet['9'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(9)->m_Frame;
	m_Small_SilverSet['A'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(10)->m_Frame;
	m_Small_SilverSet['B'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(11)->m_Frame;
	m_Small_SilverSet['C'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(12)->m_Frame;
	m_Small_SilverSet['D'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(13)->m_Frame;
	m_Small_SilverSet['E'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(14)->m_Frame;
	m_Small_SilverSet['F'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(15)->m_Frame;
	m_Small_SilverSet['G'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(16)->m_Frame;
	m_Small_SilverSet['H'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(17)->m_Frame;
	m_Small_SilverSet['I'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(18)->m_Frame;
	m_Small_SilverSet['J'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(19)->m_Frame;
	m_Small_SilverSet['K'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(20)->m_Frame;
	m_Small_SilverSet['L'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(21)->m_Frame;
	m_Small_SilverSet['M'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(22)->m_Frame;
	m_Small_SilverSet['N'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(23)->m_Frame;
	m_Small_SilverSet['O'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(24)->m_Frame;
	m_Small_SilverSet['P'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(25)->m_Frame;
	m_Small_SilverSet['Q'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(26)->m_Frame;
	m_Small_SilverSet['R'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(27)->m_Frame;
	m_Small_SilverSet['S'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(28)->m_Frame;
	m_Small_SilverSet['T'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(29)->m_Frame;
	m_Small_SilverSet['U'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(30)->m_Frame;
	m_Small_SilverSet['V'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(31)->m_Frame;
	m_Small_SilverSet['W'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(32)->m_Frame;
	m_Small_SilverSet['X'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(33)->m_Frame;
	m_Small_SilverSet['Y'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(34)->m_Frame;
	m_Small_SilverSet['Z'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_SILVER"))->GetFrameInfoByIdx(35)->m_Frame;
}
void CTextBox::SoltingNomalSilver()
{
	m_Nomal_SilverSet['0'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(0)->m_Frame;
	m_Nomal_SilverSet['1'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(1)->m_Frame;
	m_Nomal_SilverSet['2'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Nomal_SilverSet['3'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(3)->m_Frame;
	m_Nomal_SilverSet['4'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(4)->m_Frame;
	m_Nomal_SilverSet['5'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(5)->m_Frame;
	m_Nomal_SilverSet['6'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(6)->m_Frame;
	m_Nomal_SilverSet['7'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(7)->m_Frame;
	m_Nomal_SilverSet['8'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(8)->m_Frame;
	m_Nomal_SilverSet['9'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(9)->m_Frame;
	m_Nomal_SilverSet['A'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(10)->m_Frame;
	m_Nomal_SilverSet['B'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(11)->m_Frame;
	m_Nomal_SilverSet['C'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(12)->m_Frame;
	m_Nomal_SilverSet['D'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(13)->m_Frame;
	m_Nomal_SilverSet['E'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(14)->m_Frame;
	m_Nomal_SilverSet['F'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(15)->m_Frame;
	m_Nomal_SilverSet['G'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(16)->m_Frame;
	m_Nomal_SilverSet['H'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(17)->m_Frame;
	m_Nomal_SilverSet['I'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(18)->m_Frame;
	m_Nomal_SilverSet['J'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(19)->m_Frame;
	m_Nomal_SilverSet['K'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(20)->m_Frame;
	m_Nomal_SilverSet['L'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(21)->m_Frame;
	m_Nomal_SilverSet['M'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(22)->m_Frame;
	m_Nomal_SilverSet['N'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(23)->m_Frame;
	m_Nomal_SilverSet['O'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(24)->m_Frame;
	m_Nomal_SilverSet['P'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(25)->m_Frame;
	m_Nomal_SilverSet['Q'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(26)->m_Frame;
	m_Nomal_SilverSet['R'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(27)->m_Frame;
	m_Nomal_SilverSet['S'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(28)->m_Frame;
	m_Nomal_SilverSet['T'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(29)->m_Frame;
	m_Nomal_SilverSet['U'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(30)->m_Frame;
	m_Nomal_SilverSet['V'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(31)->m_Frame;
	m_Nomal_SilverSet['W'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(32)->m_Frame;
	m_Nomal_SilverSet['X'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(33)->m_Frame;
	m_Nomal_SilverSet['Y'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(34)->m_Frame;
	m_Nomal_SilverSet['Z'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("NOMAL_SILVER"))->GetFrameInfoByIdx(35)->m_Frame;
}
void CTextBox::SoltingBigSilver()
{
	m_Big_SilverSet['0'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(0)->m_Frame;
	m_Big_SilverSet['1'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(1)->m_Frame;
	m_Big_SilverSet['2'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Big_SilverSet['3'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(3)->m_Frame;
	m_Big_SilverSet['4'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(4)->m_Frame;
	m_Big_SilverSet['5'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(5)->m_Frame;
	m_Big_SilverSet['6'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(6)->m_Frame;
	m_Big_SilverSet['7'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(7)->m_Frame;
	m_Big_SilverSet['8'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(8)->m_Frame;
	m_Big_SilverSet['9'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(9)->m_Frame;
	m_Big_SilverSet['A'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(10)->m_Frame;
	m_Big_SilverSet['B'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(11)->m_Frame;
	m_Big_SilverSet['C'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(12)->m_Frame;
	m_Big_SilverSet['D'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(13)->m_Frame;
	m_Big_SilverSet['E'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(14)->m_Frame;
	m_Big_SilverSet['F'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(15)->m_Frame;
	m_Big_SilverSet['G'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(16)->m_Frame;
	m_Big_SilverSet['H'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(17)->m_Frame;
	m_Big_SilverSet['I'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(18)->m_Frame;
	m_Big_SilverSet['J'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(19)->m_Frame;
	m_Big_SilverSet['K'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(20)->m_Frame;
	m_Big_SilverSet['L'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(21)->m_Frame;
	m_Big_SilverSet['M'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(22)->m_Frame;
	m_Big_SilverSet['N'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(23)->m_Frame;
	m_Big_SilverSet['O'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(24)->m_Frame;
	m_Big_SilverSet['P'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(25)->m_Frame;
	m_Big_SilverSet['Q'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(26)->m_Frame;
	m_Big_SilverSet['R'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(27)->m_Frame;
	m_Big_SilverSet['S'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(28)->m_Frame;
	m_Big_SilverSet['T'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(29)->m_Frame;
	m_Big_SilverSet['U'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(30)->m_Frame;
	m_Big_SilverSet['V'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(31)->m_Frame;
	m_Big_SilverSet['W'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(32)->m_Frame;
	m_Big_SilverSet['X'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(33)->m_Frame;
	m_Big_SilverSet['Y'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(34)->m_Frame;
	m_Big_SilverSet['Z'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_SILVER"))->GetFrameInfoByIdx(35)->m_Frame;
}

void CTextBox::SoltingSmallGold()
{
	m_Small_GoldSet['0'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(0)->m_Frame;
	m_Small_GoldSet['1'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(1)->m_Frame;
	m_Small_GoldSet['2'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Small_GoldSet['3'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(3)->m_Frame;
	m_Small_GoldSet['4'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(4)->m_Frame;
	m_Small_GoldSet['5'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(5)->m_Frame;
	m_Small_GoldSet['6'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(6)->m_Frame;
	m_Small_GoldSet['7'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(7)->m_Frame;
	m_Small_GoldSet['8'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(8)->m_Frame;
	m_Small_GoldSet['9'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(9)->m_Frame;
	m_Small_GoldSet['A'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(10)->m_Frame;
	m_Small_GoldSet['B'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(11)->m_Frame;
	m_Small_GoldSet['C'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(12)->m_Frame;
	m_Small_GoldSet['D'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(13)->m_Frame;
	m_Small_GoldSet['E'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(14)->m_Frame;
	m_Small_GoldSet['F'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(15)->m_Frame;
	m_Small_GoldSet['G'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(16)->m_Frame;
	m_Small_GoldSet['H'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(17)->m_Frame;
	m_Small_GoldSet['I'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(18)->m_Frame;
	m_Small_GoldSet['J'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(19)->m_Frame;
	m_Small_GoldSet['K'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(20)->m_Frame;
	m_Small_GoldSet['L'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(21)->m_Frame;
	m_Small_GoldSet['M'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(22)->m_Frame;
	m_Small_GoldSet['N'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(23)->m_Frame;
	m_Small_GoldSet['O'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(24)->m_Frame;
	m_Small_GoldSet['P'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(25)->m_Frame;
	m_Small_GoldSet['Q'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(26)->m_Frame;
	m_Small_GoldSet['R'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(27)->m_Frame;
	m_Small_GoldSet['S'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(28)->m_Frame;
	m_Small_GoldSet['T'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(29)->m_Frame;
	m_Small_GoldSet['U'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(30)->m_Frame;
	m_Small_GoldSet['V'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(31)->m_Frame;
	m_Small_GoldSet['W'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(32)->m_Frame;
	m_Small_GoldSet['X'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(33)->m_Frame;
	m_Small_GoldSet['Y'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(34)->m_Frame;
	m_Small_GoldSet['Z'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("SMALL_GOLD"))->GetFrameInfoByIdx(35)->m_Frame;

}
void CTextBox::SoltingBigGold()
{
	m_Big_GoldSet['0'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(0)->m_Frame;
	m_Big_GoldSet['1'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(1)->m_Frame;
	m_Big_GoldSet['2'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(2)->m_Frame;
	m_Big_GoldSet['3'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(3)->m_Frame;
	m_Big_GoldSet['4'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(4)->m_Frame;
	m_Big_GoldSet['5'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(5)->m_Frame;
	m_Big_GoldSet['6'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(6)->m_Frame;
	m_Big_GoldSet['7'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(7)->m_Frame;
	m_Big_GoldSet['8'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(8)->m_Frame;
	m_Big_GoldSet['9'] =
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(9)->m_Frame;
	m_Big_GoldSet['N'] =		//무한대 기호.
		CAniInfoMgr::Getinst()->Get_UI_SET_1_AniSet(_T("BIG_GOLD"))->GetFrameInfoByIdx(10)->m_Frame;
}


void CTextBox::Render(HDC _hdc)
{
	/*Rectangle(_hdc,
	int(m_TextBox_X), int(m_TextBox_Y),
	int(m_TextBox_X + m_TextWidth), int(m_TextBox_Y + m_TextHeight) );*/

	PatBlt(m_TempDC, 0, 0, WINCX, WINCY, BLACKNESS);

	float Delta_X = 0;

	for (unsigned int i = 0; i < strlen(m_TextContent); ++i)
	{
		StretchBlt(m_TempDC,
			int(Delta_X), 0,
			int(m_TextBoxWidth / strlen(m_TextContent)), int(m_TextBoxHeight),
			CResourceMgr::GetInst()->GetBitDCMap("Atals_UI_Set_1")->GetMemDC(),
			int((*m_CurAniSet)[m_TextContent[i]]->GetFrameRect()->getPoint1().getX()),
			int((*m_CurAniSet)[m_TextContent[i]]->GetFrameRect()->getPoint1().getY()),
			int((*m_CurAniSet)[m_TextContent[i]]->FrameWidth),
			int((*m_CurAniSet)[m_TextContent[i]]->FrameHeight),
			SRCCOPY);

		Delta_X +=
			m_TextBoxWidth / strlen(m_TextContent) + 1;
	}
	TransparentBlt(_hdc, int(m_TextBox_X), int(m_TextBox_Y),
		int(m_TextBoxWidth), int(m_TextBoxHeight),
		m_TempDC,
		0, 0, int(m_TextBoxWidth), int(m_TextBoxHeight),
		(*m_CurAniSet)['0']->m_dwColor);
}
