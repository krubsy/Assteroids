#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class MyVector{
public:
	MyVector::MyVector();
	MyVector::MyVector(float);
	MyVector::MyVector(float x, float y) { Y = y; X = x; }


	static MyVector toOurVec(cocos2d::Vec2 v) {
		MyVector result;
		result.X = v.x;
		result.Y = v.y;
		return result;
	}

	static cocos2d::Vec2 toCocVec(MyVector v) {
		cocos2d::Vec2 result;
		result.x = v.X;
		result.y = v.Y;
		return result;
	}

	void operator+=(const MyVector temp){
		
		this->X = this->X + temp.X;
		this->Y = this->Y + temp.Y;
	}

	MyVector operator*(const MyVector temp) {
		MyVector result;
		result.X = this->X * temp.X;
		result.Y = this->Y * temp.Y;
		return result;
	}

	MyVector operator-(const MyVector temp) const {
		MyVector result;
		result.X = this->X - temp.X;
		result.Y = this->Y - temp.Y;
		return result;
	}

	MyVector getNormalized() {
		MyVector temp;
		return temp;
	}

	float X;
	float Y;
	float radius = 32;

};


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