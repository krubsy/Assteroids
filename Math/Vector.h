#pragma once
#include "cocos2d.h"
using namespace cocos2d;

typedef class Vector{
public:
	Vector::Vector();
	Vector::Vector(float);


	static Vector toOurVec(cocos2d::Vec2 v) {
		Vector result;
		result.X = v.x;
		result.Y = v.y;
		return result;
	}

	static cocos2d::Vec2 toCocVec(vec2 v) {
		cocos2d::Vec2 result;
		result.x = v.X;
		result.y = v.Y;
		return result;
	}

	void operator+=(const Vector temp){
		
		this->X = this->X + temp.X;
		this->Y = this->Y + temp.Y;
	}

	Vector operator*(const Vector temp) {
		Vector result;
		result.X = this->X * temp.X;
		result.Y = this->Y * temp.Y;
		return result;
	}

	float X;
	float Y;

}vec2;


//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------

class vec4 {
public:
	float x, y, z, w;

	vec4() = default;
	vec4(float X, float Y, float Z, float W);

	const float& operator[](const int index) const;
	float& operator[](const int index);

	vec4 operator+(const vec4 &vec) const;
	vec4 operator-(const vec4 &vec) const;
	vec4 operator*(const vec4 &vec) const;
	vec4 operator/(const vec4 &vec) const;
};