#include "stdafx.h"

const Vector3 Vector3::Zero(0.f, 0.f, 0.f);
const Vector3 Vector3::UnitX(1.0f, 0.f, 0.f);
const Vector3 Vector3::UnitY(0.f, 1.f, 0.f);
const Vector3 Vector3::UnitZ(0.f, 0.f, 1.f);

float RoboMath::GetRandomFloat()
{
	static random_device rd;
	static mt19937 gen(rd());
	uniform_real_distribution<float> dis(0.f, 1.f);
	return dis(gen);
}

Vector3 RoboMath::GetRandomVector(const Vector3& _min, const Vector3& _max)
{
	Vector3 r = Vector3(GetRandomFloat(), GetRandomFloat(), GetRandomFloat());
	return _min + (_max - _min)*r;
}