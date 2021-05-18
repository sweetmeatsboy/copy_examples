#include "stdafx.h"

const CAniDCSet::FrameInfo* CAniDCSet::GetFrameInfoByIdx(int _Idx) const
{
	auto err = ErrorMgr::GetInst().ErrBoxPopupT(_T("AniDCSet_GetFrameInfoByIdx"), _T("Error"), (unsigned)_Idx > m_FrameInfo.size());
	if (err)
		return nullptr;
	return m_FrameInfo.at(_Idx);
}
void CAniDCSet::SetAniName(const TCHAR* _Name)
{
	memset(AniName, 0, sizeof(AniName));
	wcscpy_s(AniName, _Name);
}
const TCHAR* CAniDCSet::GetName() const
{
	return AniName;
}
void CAniDCSet::AddFrameInfo(CFrameDC* _IdxFrameDC, DWORD _TimeInfo)
{
	FrameInfo* temp = new FrameInfo();
	temp->m_Frame = _IdxFrameDC;
	temp->m_FrameTimer = _TimeInfo;
	m_FrameInfo.push_back(temp);
}

int CAniDCSet::GetFrameCount() const
{
	if (m_FrameInfo.empty() == false)
		return m_FrameInfo.size();
	else
		return 0;
}
void CAniDCSet::SetAtlasMapName(string _temp)
{
	m_AtlasMapName.clear();
	m_AtlasMapName.append(_temp);
}



void CAniDCSet::RenderAniSet(HDC _hdc, int _CurFrame, float _CenterX, float _CenterY, bool _isReverse)
{
	CFrameDC* CurFrame = GetFrameInfoByIdx(_CurFrame)->m_Frame;
	PatBlt(m_TempDC, 0, 0, WINCX, WINCY, CurFrame->m_dwColor);


	if (_isReverse == false)	//원래대로 출력
	{
		StretchBlt(m_TempDC,
			0, 0,
			int(CurFrame->FrameWidth * m_Scale_X), int(CurFrame->FrameHeight * m_Scale_Y),
			CResourceMgr::GetInst()->GetBitDCMap(m_AtlasMapName)->GetCBitMapDC()->GetMemDC(),
			int(CurFrame->GetFrameRect()->getPoint1().getX()),
			int(CurFrame->GetFrameRect()->getPoint1().getY()),
			int(CurFrame->FrameWidth - 1), int(CurFrame->FrameHeight - 1),
			SRCCOPY);

		TransparentBlt(_hdc,
			int(_CenterX - CurFrame->GetCenterPoint()->getX() * m_Scale_X),
			int(_CenterY - CurFrame->GetCenterPoint()->getY() * m_Scale_Y),
			int(CurFrame->FrameWidth * m_Scale_X), int(CurFrame->FrameHeight * m_Scale_Y),
			m_TempDC,
			0, 0,
			int((CurFrame->FrameWidth) * m_Scale_X), int((CurFrame->FrameHeight) * m_Scale_Y),
			CurFrame->m_dwColor);
	}
	else
	{
		StretchBlt(m_TempDC,
			int(CurFrame->FrameWidth * m_Scale_X), 0,
			-1 * int(CurFrame->FrameWidth * m_Scale_X), int(CurFrame->FrameHeight * m_Scale_Y),
			CResourceMgr::GetInst()->GetBitDCMap(m_AtlasMapName)->GetCBitMapDC()->GetMemDC(),
			int(CurFrame->GetFrameRect()->getPoint1().getX()),
			int(CurFrame->GetFrameRect()->getPoint1().getY()),
			int(CurFrame->FrameWidth), int(CurFrame->FrameHeight),
			SRCCOPY);
		TransparentBlt(_hdc,
			int(_CenterX - (CurFrame->FrameWidth - CurFrame->GetCenterPoint()->getX())*m_Scale_X),
			int(_CenterY - CurFrame->GetCenterPoint()->getY()*m_Scale_Y),
			int(CurFrame->FrameWidth * m_Scale_X), int(CurFrame->FrameHeight * m_Scale_Y),
			m_TempDC,
			0, 0,
			int(CurFrame->FrameWidth * m_Scale_X), int(CurFrame->FrameHeight * m_Scale_Y),
			CurFrame->m_dwColor);
	}
}
void CAniDCSet::Release()
{
	memset(AniName, 0, sizeof(AniName));

	for (vector<FrameInfo*>::iterator tempIter = m_FrameInfo.begin();
		tempIter != m_FrameInfo.end(); ++tempIter)
	{
		delete (*tempIter)->m_Frame;
		(*tempIter) = NULL;
	}
	m_FrameInfo.clear();
	swap(*(new vector<FrameInfo*>()), m_FrameInfo);

	DeleteDC(m_TempDC);
}
