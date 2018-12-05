#include "Math/Vector.h"

MyVector::MyVector()
{
	X = 0.0f;
	Y = 0.0f;
}

MyVector::MyVector(float f)
{
	X = f;
	Y = f;
}

//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

vec4::vec4(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

const float & vec4::operator[](const int index) const {
	return (&x)[index]; //offsets address of x by index
}

float & vec4::operator[](const int index)
{
	return (&x)[index];
}

vec4 vec4::operator+(const vec4 & vec) const
{
	return vec4(x + vec.x, y + vec.y, z + vec.y, w + vec.w);
}
vec4 vec4::operator-(const vec4 & vec) const
{
	return vec4(x - vec.x, y - vec.y, z - vec.y, w - vec.w);
}
vec4 vec4::operator*(const vec4 & vec) const
{
	return vec4(x * vec.x, y * vec.y, z * vec.y, w * vec.w);
}
vec4 vec4::operator/(const vec4 & vec) const
{
	return vec4(x / vec.x, y / vec.y, z / vec.y, w / vec.w);
}


