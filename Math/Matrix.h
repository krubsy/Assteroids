#pragma once
#include "Vector.h"
#include <ostream>
#include <iostream>

class mat4{

public:
	vec4 col[4];
	mat4();

	mat4(const vec4 right, const vec4 up, const vec4 dir, const vec4 pos);
	mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15);
	mat4::mat4(std::string s);


	const vec4 operator[](const int index) const;
	vec4 operator[](const int index);

	void RotateZ(float degrees);

	mat4 operator+(const mat4 &m) const;
	mat4 operator-(const mat4 &m) const;
	mat4 operator*(const mat4 &m) const;
	vec4 operator*(const vec4 &v) const;

	mat4 getTranspose() const;
};

inline std::ostream& operator<<(std::ostream& os, const mat4& m) {

	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			os << m[col][row] << "\t";
		}
		os << "\n";
	}
	return os;
}

//mat4 matrix;
//matrix[1][1]; //we are getting values at the first collum and first row