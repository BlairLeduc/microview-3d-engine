#include <math.h>
#include <MicroView.h>
#include "3dengine.h"
#include "shape.h"

Device::Device()
{
	uView.begin();
	uView.clear(PAGE);
	width = uView.getLCDWidth();
	height = uView.getLCDHeight();
}

void Device::clear()
{
	uView.clear(PAGE);
}

void Device::present()
{
	uView.display();
}

Vector3 Device::project(Vector3 coord, Matrix transMat)
{
	Vector3 point = Vector3::transformCoordinate(coord, transMat);

	float x = point.x * width + width / 2.0;
	float y = -point.y * height + height / 2.0;

	return Vector3(x, y, point.z);
}

void Device::drawPoint(Vector3 point)
{
	uView.pixel((int)point.x, (int)point.y, WHITE, NORM);
}

void Device::drawLine(Vector3 point0, Vector3 point1)
{
	int x = (int)point0.x;
	int y = (int)point0.y;
	int x2 = (int)point1.x;
	int y2 = (int)point1.y;

	// Extremely Fast Line Algorithm (Po-Han Lin)
	// http://www.edepot.com
	
	bool yLonger = false;
	int shortLen = y2 - y;
	int longLen = x2 - x;
	if (abs(shortLen) > abs(longLen))
	{
		int swap = shortLen;
		shortLen = longLen;
		longLen = swap;
		yLonger = true;
	}
	int decInc;
	if (longLen == 0) decInc = 0;
	else decInc = (shortLen << 8) / longLen;

	if (yLonger)
	{
		if (longLen > 0)
		{
			longLen += y;
			for (int j = 0x80 + (x << 8); y <= longLen; ++y)
			{
				uView.pixel(j >> 8, y, WHITE, NORM);
				j += decInc;
			}
			return;
		}
		longLen += y;
		for (int j = 0x80 + (x << 8); y >= longLen; --y)
		{
			uView.pixel(j >> 8, y, WHITE, NORM);
			j -= decInc;
		}
		return;
	}

	if (longLen > 0)
	{
		longLen += x;
		for (int j = 0x80 + (y << 8); x <= longLen; ++x)
		{
			uView.pixel(x, j >> 8, WHITE, NORM);
			j += decInc;
		}
		return;
	}
	longLen += x;
	for (int j = 0x80 + (y << 8); x >= longLen; --x)
	{
		uView.pixel(x, j >> 8, WHITE, NORM);
		j -= decInc;
	}
}

void Device::render(Camera *camera, Mesh **meshes, int numberOfMeshes)
{
	Matrix viewMatrix = Matrix::lookAtLH(camera->position, camera->target, Vector3::up());
	Matrix projectionMatrix = Matrix::perspectiveFovLH(0.78, width / height, 0.01, 1.0);

	for(int i = 0; i < numberOfMeshes; i++)
	{
		Mesh *mesh = meshes[i];
		Matrix worldMatrix = Matrix::rotationYawPitchRoll(mesh->rotation.y,
		                     mesh->rotation.x,
		                     mesh->rotation.z) *
		                     Matrix::translation(mesh->position);

		Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

#ifdef VERTICES_ONLY
		// This loop only draws the vertices, great for debuging
		for(int j=0; j < mesh->numberOfVertices; j++)
		{
			drawPoint(project(mesh->vertices[j], transformMatrix));
		}
#else
		// This loop draws the triangles
		for(int j = 0; j < mesh->numberOfFaces; j++)
		{
			Face face = mesh->faces[j];

			Vector3 vertexA = mesh->vertices[face.a];
			Vector3 vertexB = mesh->vertices[face.b];
			Vector3 vertexC = mesh->vertices[face.c];

			Vector3 pixelA = project(vertexA, transformMatrix);
			Vector3 pixelB = project(vertexB, transformMatrix);
			Vector3 pixelC = project(vertexC, transformMatrix);

			Vector3 u = pixelB - pixelA;
			Vector3 v = pixelC - pixelA;

			Vector3 normal = Vector3::cross(u, v);

			float result = Vector3::dot(camera->position - pixelA, normal);

			if (result < 0.0)
			{

				drawLine(pixelA, pixelB);
				drawLine(pixelB, pixelC);
#ifndef CUBE
				// Leaving this out removes the diagonal lines on the
				// cubes surface.
				drawLine(pixelA, pixelC);
#endif
			}
		}
#endif		
	}
}

