#pragma once

class CScene
{
public:

	explicit CScene(const CRc& rcMain = CRc(), const CPt& ptMain = CPt());
	~CScene();
	CScene(const CScene& rScene);
	CScene& operator=(const CScene& rScene);

	const CRc& getMainRect() const;
	const CPt& getMainPoint() const;

	void setMainRect(CPt::PT_TYPE left, CPt::PT_TYPE up
		, CPt::PT_TYPE right, CPt::PT_TYPE down);
	void setMainRect(const CPt& rPoint1, const CPt& rPoint2);
	void setMainRect(const CRc& rRc);

	void setMainPoint(CPt::PT_TYPE x, CPt::PT_TYPE y);
	void setMainPoint(const CPt& rPoint);

	void pushCollisionRect(const CRc& rRc); // 충동영역 추가

	const CRc* getCollisionRect(CPt::PT_TYPE x, CPt::PT_TYPE y) const; // 충돌영역 얻기
	const CRc* getCollisionRect(const CPt& rPoint) const; // 충돌영역 얻기 (없으면 NULL반환)

	const CRc& getCollisionRect(int iIndex) const; /// 인덱스 참조

	std::vector<CRc*>::size_type getCountOfCollisionRect() const;

	// 화면상의 자신의 좌표, 확인할 장면, 확인할 장면의 화면상 좌표
	bool testCollisionScene(const CPt& ptPos, const CScene& rScene, const CPt& ptPos2) const; // 충돌 확인(2차 충돌영역까지 확인)

	void deleteCollisionRect(const CRc& rRc);

	void clearCollisionRect();

public:

	CRc m_rcMain;
	CPt m_ptMain;

	std::vector<CRc*> m_rcCollisions; // 충돌 영역들
};