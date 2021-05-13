#pragma once


class CPt
{
public:
	typedef float PT_TYPE;
private:
	PT_TYPE m_x;
	PT_TYPE m_y;
public:
	explicit CPt(PT_TYPE x = 0, PT_TYPE y = 0);
	~CPt();
	CPt(const CPt& _ref);
	CPt& operator =(const CPt& _ref);

	PT_TYPE getX()const;
	PT_TYPE getY()const;

	void setX(PT_TYPE _x);
	void setY(PT_TYPE _y);

	double distance(PT_TYPE _x, PT_TYPE _y);
	double distance(const CPt& _ref);

	const CPt operator +(const CPt& _ref) const;
	const CPt operator -(const CPt& _ref) const;
	CPt& operator +=(const CPt& _ref);
	CPt& operator -=(const CPt& _ref);
	bool operator ==(const CPt& _ref) const;
public:
	CPt getUnitVector();
};