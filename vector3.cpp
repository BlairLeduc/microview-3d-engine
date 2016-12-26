#include <math.h>
#include "3dengine.h"

Vector3::Vector3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator-(const Vector3& other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::zero()
{
	return Vector3();
}

Vector3 Vector3::up()
{
	return Vector3(0, 1, 0);

}

Vector3 Vector3::transformCoordinate(Vector3 vector, Matrix transformation)
{
	Vector3 result;

	float x = (vector.x * transformation.m[0]) + (vector.y * transformation.m[4]) + (vector.z * transformation.m[8]) + transformation.m[12];
	float y = (vector.x * transformation.m[1]) + (vector.y * transformation.m[5]) + (vector.z * transformation.m[9]) + transformation.m[13];
	float z = (vector.x * transformation.m[2]) + (vector.y * transformation.m[6]) + (vector.z * transformation.m[10]) + transformation.m[14];
	float w = (vector.x * transformation.m[3]) + (vector.y * transformation.m[7]) + (vector.z * transformation.m[11]) + transformation.m[15];

	result.x = x / w;
	result.y = y / w;
	result.z = z / w;

	return result;
}

Vector3 Vector3::cross(Vector3 left, Vector3 right)
{
	Vector3 result;

	result.x = left.y * right.z - left.z * right.y;
	result.y = left.z * right.x - left.x * right.z;
	result.z = left.x * right.y - left.y * right.x;

	return result;
}

float Vector3::dot(Vector3 left, Vector3 right)
{
	return (left.x * right.x + left.y * right.y + left.z * right.z);
}

float Vector3::length()
{
	return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize()
{
	float len = length();

	if (len == 0)
	{
		return;
	}

	float num = 1.0 / len;

	x *= num;
	y *= num;
	z *= num;
}
