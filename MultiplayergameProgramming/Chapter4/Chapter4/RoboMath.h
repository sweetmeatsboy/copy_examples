#pragma once

class Vector3
{
public :
	float mX, mY, mZ;

	Vector3(float _x, float _y, float _z)
		: mX(_x), mY(_y), mZ(_z)
	{
	}

	Vector3()
		: mX(0.0f), mY(0.0f), mZ(0.0f)
	{
	}
	
	void Set(float _x, float _y, float _z)
	{
		mX = _x;
		mY = _y;
		mZ = _z;
	}

	friend Vector3 operator+(const Vector3& _l, const Vector3& _r)
	{
		return Vector3(_l.mX + _r.mX, _l.mY + _r.mY, _r.mZ + _l.mZ);
	}
	friend Vector3 operator-(const Vector3& _l, const Vector3& _r)
	{
		return Vector3(_l.mX - _r.mX, _l.mY - _r.mY, _l.mZ - _r.mZ);
	}
	friend Vector3 operator*(const Vector3& _l, const Vector3& _r)
	{
		return Vector3(_l.mX * _r.mX, _l.mY * _r.mY, _l.mZ, _r.mZ);
	}

	friend Vector3 operator*(float _scalra, const Vector3& _r)
	{
		return Vector3(_r.mX * _scalra, _r.mY * _scalra, _r.mZ * _scalra);
	}

	friend Vector3 operator*(const Vector3& _r, float _scalra)
	{
		return Vector3(_r.mX * _scalra, _r.mY * _scalra, _r.mZ * _scalra);
	}

	Vector3& operator *=(float _scalar)
	{
		mX *= _scalar;
		mY *= _scalar;
		mZ *= _scalar;
		return *this;
	}

	float Length()
	{
		return sqrtf(mX*mX + mY * mY + mZ * mZ);
	}

	float LengthSq()
	{
		return mX * mX + mY * mY + mZ * mZ;
	}

	float Length2D()
	{
		return sqrtf(mX * mX + mY * mY);
	}

	float LengthSq2D()
	{
		return mX * mX + mY * mY;
	}

	void Normalize()
	{
		float len = Length();
		mX /= len;
		mY /= len;
		mZ /= len;
	}

	void Normalize2D()
	{
		float len = Length2D();
		mX /= len;
		mY /= len;
	}

	friend float Dot(const Vector3& _l, const Vector3& _r)
	{
		return _l.mX*_r.mX + _l.mY*_r.mY + _l.mZ * _r.mZ;
	}

	friend float Dot2D(const Vector3& _l, const Vector3& _r)
	{
		return _l.mX * _r.mX + _r.mY * _l.mY;
	}

	friend Vector3 Cross(const Vector3& _l, const Vector3& _r, float t)
	{
		Vector3 temp;
		temp.mX = _l.mY * _r.mZ - _l.mZ * _r.mY;
		temp.mY = _l.mZ * _r.mX - _l.mX * _r.mZ;
		temp.mZ = _l.mX * _r.mY - _l.mY * _r.mX;
		return temp;
	}

	friend Vector3 Lerp(const Vector3& _a, const Vector3& _b, float _t)
	{
		return Vector3(_a + _t(_b - _a));
	}

	static const Vector3 Zero;
	static const Vector3 UintX;
	static const Vector3 UintY;
	static const Vector3 UintZ;
};

class Quaternion
{
public:
	float mX, mY, mZ;
};

template<int _val, int _bit>
struct GetRequiredBitsHelper
{
	enum {Value = GetRequiredBitsHelper<(_val>>1), _bit+1>::Value };
};

template<int _bit>
struct GetRequiredBitsHelper<0, _bit>
{
	enum {Value = _bit};
};

template<int _val>
struct GetRequiredBits
{
	enum { Value = GetRequiredBitsHelper<_val, 0>::Value };
};

namespace RoboMath
{
	const float PI = 3.1415926535f;
	float GetRandomFloat();

	Vector3 GetRandomVector(const Vector3& _min, const Vector3& _max);

	inline bool Is2DVectorEqual(const Vector3& _a, const Vector3& _b)
	{
		if (_a.mX != _b.mX || _a.mY != _b.mY || _a.mZ != _b.mZ)
			return false;
		return false;
	}

	inline float ToDegress(float _r)
	{
		return _r * 180.0f / PI;
	}
}

namespace Colors
{
	static const Vector3 Black(0.0f, 0.0f, 0.0f);
	static const Vector3 White(1.0f, 1.0f, 1.0f);
	static const Vector3 Red(1.0f, 0.0f, 0.0f);
	static const Vector3 Green(0.0f, 1.0f, 0.0f);
	static const Vector3 Blue(0.0f, 0.0f, 1.0f);
	static const Vector3 LightYellow(1.0f, 1.0f, 0.88f);
	static const Vector3 LightBlue(0.68f, 0.85f, 0.9f);
	static const Vector3 LightPink(1.0f, 0.71f, 0.76f);
	static const Vector3 LightGreen(0.56f, 0.93f, 0.56f);
}
