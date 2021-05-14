#pragma once


typedef CPt::PT_TYPE PTTYPE;

class CRc
{
private :
	CPt m_point1;
	CPt m_point2;
private :
	void Arrangement();

public:
	CRc();
	CRc(const CRc& _other);
	CRc(PTTYPE _l, PTTYPE _u, PTTYPE _r, PTTYPE _d);
	CRc(const CPt& _p1, const CPt& _p2);
	~CRc();
	CRc& operator = (const CRc& _other);
	bool operator == (const CRc& _other) const;
public:
	const CPt& getPoint1() const;
	const CPt& getPoint2() const;

	PTTYPE getWidth() const;
	PTTYPE getHeight() const;
	PTTYPE getLeft() const;
	PTTYPE getRight() const;
	PTTYPE getUp() const;
	PTTYPE getDown() const;
	PTTYPE getArea() const;

	void setLeft(PTTYPE _val);
	void setUp(PTTYPE _val);
	void setRight(PTTYPE _val);
	void setDown(PTTYPE _val);

	void setPoint1(const CPt& _p);
	void setPoint2(const CPt& _p);

	bool testCollision(PTTYPE _l, PTTYPE _u, PTTYPE _r, PTTYPE _d) const;
	bool testCollision(const CPt& _p1, const CPt& _p2) const;
	bool testCollision(const CRc& _other) const;

	// 좌표 포함 확인
	bool testInclusion(PTTYPE x, PTTYPE y) const;
	bool testInclusion(const CPt& rPoint) const;
};

