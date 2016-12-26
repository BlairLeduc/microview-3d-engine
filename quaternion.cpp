#include <math.h>
#include "3dengine.h"

Quaternion::Quaternion()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Quaternion Quaternion::rotationYawPitchRoll(float yaw, float pitch, float roll)
{
	float halfRoll = roll * 0.5;
	float halfPitch = pitch * 0.5;
	float halfYaw = yaw * 0.5;

	float sinRoll = sin(halfRoll);
	float cosRoll = cos(halfRoll);
	float sinPitch = sin(halfPitch);
	float cosPitch = cos(halfPitch);
	float sinYaw = sin(halfYaw);
	float cosYaw = cos(halfYaw);

	Quaternion result;

	result.x = (cosYaw * sinPitch * cosRoll) + (sinYaw * cosPitch * sinRoll);
	result.y = (sinYaw * cosPitch * cosRoll) - (cosYaw * sinPitch * sinRoll);
	result.z = (cosYaw * cosPitch * sinRoll) - (sinYaw * sinPitch * cosRoll);
	result.w = (cosYaw * cosPitch * cosRoll) + (sinYaw * sinPitch * sinRoll);

	return result;
}

Matrix Quaternion::toRotationMatrix()
{
	float xx = x * x;
	float yy = y * y;
	float zz = z * z;
	float xy = x * y;
	float zw = z * w;
	float zx = z * x;
	float yw = y * w;
	float yz = y * z;
	float xw = x * w;

	Matrix result;

	result.m[0] = 1.0 - (2.0 * (yy + zz));
	result.m[1] = 2.0 * (xy + zw);
	result.m[2] = 2.0 * (zx - yw);
	result.m[3] = 0;
	result.m[4] = 2.0 * (xy - zw);
	result.m[5] = 1.0 - (2.0 * (zz + xx));
	result.m[6] = 2.0 * (yz + xw);
	result.m[7] = 0;
	result.m[8] = 2.0 * (zx + yw);
	result.m[9] = 2.0 * (yz - xw);
	result.m[10] = 1.0 - (2.0 * (yy + xx));
	result.m[11] = 0;
	result.m[12] = 0;
	result.m[13] = 0;
	result.m[14] = 0;
	result.m[15] = 1.0;

	return result;
}
