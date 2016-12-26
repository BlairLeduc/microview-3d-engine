#include "3dengine.h"

Mesh::Mesh(int numberOfVertices, int numberOfFaces)
{
	this->numberOfVertices = numberOfVertices;
	this->vertices = new Vector3[numberOfVertices];
	this->numberOfFaces = numberOfFaces;
	this->faces = new Face[numberOfFaces];
}
