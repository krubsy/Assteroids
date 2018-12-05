#include "proj.win32/Math/Matrix.h"

mat4::mat4()
{
	col[0][0] = 0.0f;
	col[0][1] = 0.0f;
	col[0][2] = 0.0f;
	col[0][3] = 0.0f;

	col[1][0] = 1.0f;
	col[1][1] = 0.0f;
	col[1][2] = 0.0f;
	col[1][3] = 0.0f;

	col[0][0] = 0.0f;
	col[0][1] = 1.0f;
	col[0][2] = 0.0f;
	col[0][3] = 0.0f;

	col[2][0] = 0.0f;
	col[2][1] = 0.0f;
	col[2][2] = 1.0f;
	col[2][3] = 0.0f;

	col[3][0] = 0.0f;
	col[3][1] = 0.0f;
	col[3][2] = 0.0f;
	col[3][3] = 1.0f;

}

mat4::mat4(const vec4 right, const vec4 up, const vec4 dir, const vec4 pos)
{
	col[0] = right;
	col[1] = up;
	col[2] = dir;
	col[3] = pos;
}

mat4::mat4(float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, float f10, float f11, float f12, float f13, float f14, float f15)
{
	col[0][0] = f0;
	col[0][1] = f1;
	col[0][2] = f2;
	col[0][3] = f3;
	col[1][0] = f4;
	col[1][1] = f5;
	col[1][2] = f6;
	col[1][3] = f7;
	col[2][0] = f8;
	col[2][1] = f9;
	col[2][2] = f10;
	col[2][3] = f11;
	col[3][0] = f12;
	col[3][1] = f13;
	col[3][2] = f14;
	col[3][3] = f15;
}

const vec4 mat4::operator[](const int index) const
{
	return col[index];
}

vec4 mat4::operator[](const int index)
{
	return col[index];
}

mat4 mat4::operator+(const mat4 & m) const
{
	return mat4(col[0] + m[0],
		col[1] + m[1],
		col[2] + m[2],
		col[3] + m[3]);
}

mat4 mat4::operator-(const mat4 & m) const
{
	return mat4(col[0] - m[0],
		col[1] - m[1],
		col[2] - m[2],
		col[3] - m[3]);
}

mat4 mat4::operator*(const mat4 & m) const
{
	//basically giant dot product
	return mat4(
		col[0][0] * m[0][0] + col[1][0] * m[0][1] + col[2][0] * m[0][2] + col[3][0] * m[0][3],
		col[0][0] * m[1][0] + col[1][1] * m[2][0] + col[2][0] * m[1][2] + col[3][0] * m[1][3],
		col[0][0] * m[2][0] + col[1][0] * m[2][1] + col[2][0] * m[2][2] + col[3][0] * m[2][3],
		col[0][0] * m[3][0] + col[1][0] * m[3][1] + col[2][0] * m[3][2] + col[3][0] * m[3][3],

		col[0][1] * m[0][0] + col[1][1] * m[0][1] + col[2][1] * m[0][2] + col[3][1] * m[0][3],
		col[0][1] * m[1][0] + col[1][1] * m[2][1] + col[2][1] * m[1][2] + col[3][1] * m[1][3],
		col[0][1] * m[2][0] + col[1][1] * m[2][1] + col[2][1] * m[2][2] + col[3][1] * m[2][3],
		col[0][1] * m[3][0] + col[1][1] * m[3][1] + col[2][1] * m[3][2] + col[3][1] * m[3][3],

		col[0][2] * m[0][0] + col[1][2] * m[0][1] + col[2][2] * m[0][2] + col[3][2] * m[0][3],
		col[0][2] * m[1][0] + col[1][2] * m[2][1] + col[2][2] * m[1][2] + col[3][2] * m[1][3],
		col[0][2] * m[2][0] + col[1][2] * m[2][1] + col[2][2] * m[2][2] + col[3][2] * m[2][3],
		col[0][2] * m[3][0] + col[1][2] * m[3][1] + col[2][2] * m[3][2] + col[3][2] * m[3][3],

		col[0][3] * m[0][0] + col[1][3] * m[0][1] + col[2][3] * m[0][2] + col[3][3] * m[0][3],
		col[0][3] * m[1][0] + col[1][3] * m[2][1] + col[2][3] * m[1][2] + col[3][3] * m[1][3],
		col[0][3] * m[2][0] + col[1][3] * m[2][1] + col[2][3] * m[2][2] + col[3][3] * m[2][3],
		col[0][3] * m[3][0] + col[1][3] * m[3][1] + col[2][3] * m[3][2] + col[3][3] * m[3][3]);
}

void mat4::RotateZ(float degrees)
{

	//[cos(-Z Angle) - sin(-Z Angle) 0 0]
	//[sin(-Z Angle) cos(-Z Angle) 0 0]
	//[0 0 1 0]
	//[0 0 0 1]

	mat4 temp;
	temp[0][0] = cos(-degrees);
	temp[1][0] = sin(-degrees);
	temp[2][0] = 0;
	temp[3][0] = 0;

	temp[0][1] = -sin(-degrees);
	temp[1][1] = cos(-degrees);
	temp[2][1] = 0;
	temp[3][1] = 0;

	temp[0][2] = 0;
	temp[1][2] = 0;
	temp[2][2] = 1;
	temp[3][2] = 0;

	temp[0][3] = 0;
	temp[1][3] = 0;
	temp[2][3] = 0;
	temp[3][3] = 1;

}
mat4 mat4::getTranspose() const
{
	mat4 temp;
	temp[0][0] = col[0][0];
	temp[1][0] = col[0][1];
	temp[2][0] = col[0][2];
	temp[3][0] = col[0][3];

	temp[0][1] = col[1][0];
	temp[1][1] = col[1][1];
	temp[2][1] = col[1][2];
	temp[3][1] = col[1][3];

	temp[0][2] = col[2][0];
	temp[1][2] = col[2][1];
	temp[2][2] = col[2][2];
	temp[3][2] = col[2][3];

	temp[0][3] = col[3][0];
	temp[1][3] = col[3][1];
	temp[2][3] = col[3][2];
	temp[3][3] = col[3][3];

	return temp;
}

