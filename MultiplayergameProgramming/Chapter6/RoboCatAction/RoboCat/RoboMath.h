#pragma once

class Vector3
{
public:
	static const Vector3 Zero;
	static const Vector3 UnitX;
	static const Vector3 UnitY;
	static const Vector3 UnitZ;
public:
	float x, y, z;
	Vector3()
		: x(0.f), y(0.f), z(0.f)
	{
	}
	Vector3(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{
	}

	void Set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	friend Vector3 operator+(const Vector3& _l, const Vector3& _r)
	{
		return Vector3(_l.x + _r.x, _l.y + _r.y, _l.z + _r.x);
	}

	friend Vector3 operator-(const Vector3& _l, const Vector3& _r)
	{
		return Vector3(_l.x - _r.x, _l.y - _r.y, _l.z - _r.x);
	}

	friend Vector3 operator*(const Vector3 _l, const Vector3& _r)
	{
		return Vector3(_l.x *_r.x, _l.y * _r.y, _l.z*_r.z);
	}

	friend Vector3 operator*(const float _s, Vector3& _vect)
	{
		return Vector3(_s*_vect.x, _s*_vect.y, _s*_vect.z);
	}
	friend Vector3 operator*(Vector3& _vect, const float _s)
	{
		return Vector3(_s*_vect.x, _s*_vect.y, _s*_vect.z);
	}
	Vector3& operator*=(float inScalar)
	{
		x *= inScalar;
		y *= inScalar;
		z *= inScalar;
		return *this;
	}

	Vector3& operator+=(const Vector3& inRight)
	{
		x += inRight.x;
		y += inRight.y;
		z += inRight.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& inRight)
	{
		x -= inRight.x;
		y -= inRight.y;
		z -= inRight.z;
		return *this;
	}

	float Len()
	{
		return sqrtf(x*x + y * y + z * z);
	}

	float LenSq()
	{
		return x * x + y * y + z * z;
	}

	float Len2D()
	{
		return sqrtf(x* x + y * y);
	}
	float LenSq2D()
	{
		return x* x + y * y;
	}

	void Normalize()
	{
		float len = Len();
		x /= len;
		y /= len;
		z /= len;
	}

	void Normalize2D()
	{
		float len = Len2D();
		x /= len;
		y /= len;
	}

	friend float Dot(const Vector3& _l, const Vector3& _r)
	{
		return (_l.x * _r.x + _l.y + _r.y + _l.z * _r.z);
	}

	friend float Dot2D(const Vector3& _l, const Vector3& _r)
	{
		return (_l.x * _r.x + _l.y + _r.y);
	}

	friend Vector3 Cross(const Vector3& _l, const Vector3& _r)
	{
		Vector3 tmp;
		tmp.x = _l.y* _r.z - _l.z * _r.y;
		tmp.y = _l.z* _r.x - _l.x * _r.z;
		tmp.z = _l.x* _r.y - _l.y * _r.x;
		return tmp;
	}

	friend Vector3 Lerp(const Vector3& _a, const Vector3& _b, float _t)
	{
		return Vector3(_a + _t * (_b - _a));
	}
};


class Quaternion
{
public:

	float		mX, mY, mZ, mW;

};


template< int tValue, int tBits >
struct GetRequiredBitsHelper
{
	enum { Value = GetRequiredBitsHelper< (tValue >> 1), tBits + 1 >::Value };
};

template< int tBits >
struct GetRequiredBitsHelper< 0, tBits >
{
	enum { Value = tBits };
};

template< int tValue >
struct GetRequiredBits
{
	enum { Value = GetRequiredBitsHelper< tValue, 0 >::Value };
};

namespace RoboMath
{
	const float PI = 3.1415926535f;
	float GetRandomFloat();

	Vector3 GetRandomVector(const Vector3& inMin, const Vector3& inMax);

	inline bool	Is2DVectorEqual(const Vector3& inA, const Vector3& inB)
	{
		return (inA.x == inB.x && inA.y == inB.y);
	}

	inline float ToDegrees(float inRadians)
	{
		return inRadians * 180.0f / PI;
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
