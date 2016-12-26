#include <math.h>
#include <string.h>
#include "3dengine.h"

Matrix::Matrix()
{
	memset(this, 0, sizeof(Matrix));
}

Matrix::Matrix(float m[16])
{
	memcpy(this->m, m, sizeof(float[16]));
}

Matrix::Matrix(float initialM11, float initialM12, float initialM13, float initialM14,
               float initialM21, float initialM22, float initialM23, float initialM24,
               float initialM31, float initialM32, float initialM33, float initialM34,
               float initialM41, float initialM42, float initialM43, float initialM44)
{
	this->m[0] = initialM11;
	this->m[1] = initialM12;
	this->m[2] = initialM13;
	this->m[3] = initialM14;
	this->m[4] = initialM21;
	this->m[5] = initialM22;
	this->m[6] = initialM23;
	this->m[7] = initialM24;
	this->m[8] = initialM31;
	this->m[9] = initialM32;
	this->m[10] = initialM33;
	this->m[11] = initialM34;
	this->m[12] = initialM41;
	this->m[13] = initialM42;
	this->m[14] = initialM43;
	this->m[15] = initialM44;
}


Matrix Matrix::operator*(const Matrix& other)
{
	float tm0 = m[0];
	float tm1 = m[1];
	float tm2 = m[2];
	float tm3 = m[3];
	float tm4 = m[4];
	float tm5 = m[5];
	float tm6 = m[6];
	float tm7 = m[7];
	float tm8 = m[8];
	float tm9 = m[9];
	float tm10 = m[10];
	float tm11 = m[11];
	float tm12 = m[12];
	float tm13 = m[13];
	float tm14 = m[14];
	float tm15 = m[15];

	float om0 = other.m[0];
	float om1 = other.m[1];
	float om2 = other.m[2];
	float om3 = other.m[3];
	float om4 = other.m[4];
	float om5 = other.m[5];
	float om6 = other.m[6];
	float om7 = other.m[7];
	float om8 = other.m[8];
	float om9 = other.m[9];
	float om10 = other.m[10];
	float om11 = other.m[11];
	float om12 = other.m[12];
	float om13 = other.m[13];
	float om14 = other.m[14];
	float om15 = other.m[15];

	float result[16];
	int offset = 0;

	result[offset] = tm0 * om0 + tm1 * om4 + tm2 * om8 + tm3 * om12;
	result[offset + 1] = tm0 * om1 + tm1 * om5 + tm2 * om9 + tm3 * om13;
	result[offset + 2] = tm0 * om2 + tm1 * om6 + tm2 * om10 + tm3 * om14;
	result[offset + 3] = tm0 * om3 + tm1 * om7 + tm2 * om11 + tm3 * om15;

	result[offset + 4] = tm4 * om0 + tm5 * om4 + tm6 * om8 + tm7 * om12;
	result[offset + 5] = tm4 * om1 + tm5 * om5 + tm6 * om9 + tm7 * om13;
	result[offset + 6] = tm4 * om2 + tm5 * om6 + tm6 * om10 + tm7 * om14;
	result[offset + 7] = tm4 * om3 + tm5 * om7 + tm6 * om11 + tm7 * om15;

	result[offset + 8] = tm8 * om0 + tm9 * om4 + tm10 * om8 + tm11 * om12;
	result[offset + 9] = tm8 * om1 + tm9 * om5 + tm10 * om9 + tm11 * om13;
	result[offset + 10] = tm8 * om2 + tm9 * om6 + tm10 * om10 + tm11 * om14;
	result[offset + 11] = tm8 * om3 + tm9 * om7 + tm10 * om11 + tm11 * om15;

	result[offset + 12] = tm12 * om0 + tm13 * om4 + tm14 * om8 + tm15 * om12;
	result[offset + 13] = tm12 * om1 + tm13 * om5 + tm14 * om9 + tm15 * om13;
	result[offset + 14] = tm12 * om2 + tm13 * om6 + tm14 * om10 + tm15 * om14;
	result[offset + 15] = tm12 * om3 + tm13 * om7 + tm14 * om11 + tm15 * om15;

	return Matrix(result);
}

Matrix Matrix::zero()
{
	return Matrix();
}

Matrix Matrix::identity()
{
	return Matrix(1, 0, 0, 0,
	              0, 1, 0, 0,
	              0, 0, 1, 0,
	              0, 0, 0, 1);
}

Matrix Matrix::translation(Vector3 vector)
{
	return Matrix(1, 0, 0, 0,
	              0, 1, 0, 0,
	              0, 0, 1, 0,
	              vector.x, vector.y, vector.z, 1);
}

Matrix Matrix::translation(float x, float y, float z)
{
	return Matrix(1, 0, 0, 0,
	              0, 1, 0, 0,
	              0, 0, 1, 0,
	              x, y, z, 1);
}

Matrix Matrix::lookAtLH(Vector3 eye, Vector3 target, Vector3 up)
{
	// Z Axis
	Vector3 zAxis = target - eye;
	zAxis.normalize();

	// X Axis
	Vector3 xAxis = Vector3::cross(up, zAxis);
	xAxis.normalize();

	// Y Axis
	Vector3 yAxis = Vector3::cross(zAxis, xAxis);
	yAxis.normalize();

	// Eye Angles
	float ex = -Vector3::dot(xAxis, eye);
	float ey = -Vector3::dot(yAxis, eye);
	float ez = -Vector3::dot(zAxis, eye);

	return Matrix(xAxis.x, yAxis.x, zAxis.x, 0,
	              xAxis.y, yAxis.y, zAxis.y, 0,
	              xAxis.z, yAxis.z, zAxis.z, 0,
	              ex, ey, ez, 1);
}

Matrix Matrix::perspectiveFovLH(float fov, float aspect, float znear, float zfar)
{
	Matrix result;
	float t = 1.0 / (tan(fov * 0.5));

	result.m[0] = t / aspect;
	result.m[1] = result.m[2] = result.m[3] = 0.0;
	result.m[5] = t;
	result.m[4] = result.m[6] = result.m[7] = 0.0;
	result.m[8] = result.m[9] = 0.0;
	result.m[10] = -zfar / (znear - zfar);
	result.m[11] = 1.0;
	result.m[12] = result.m[13] = result.m[15] = 0.0;
	result.m[14] = (znear * zfar) / (znear - zfar);

	return result;
}

Matrix Matrix::rotationYawPitchRoll(float yaw, float pitch, float roll)
{
	return Quaternion::rotationYawPitchRoll(yaw, pitch, roll).toRotationMatrix();
}
