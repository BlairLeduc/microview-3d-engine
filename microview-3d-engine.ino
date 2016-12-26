#include <MicroView.h>
#include <math.h>
#include "3dengine.h"

// Choose a shape in this header file:
#include "shape.h"

Device *device;
Camera *camera;
Mesh *meshes[1];

void setup()
{
	int cameraLocation = 8;
	device = new Device();
    /*
    	3D Cube mesh:
    	
		  4--------5       Left hand
    	 /|       /|       +y
	    0--------1 |       |
		| |      | |       +-- +x
		| 7------|-6      /
		|/       |/      +z
		3--------2
		
		Origin at center of 2x2 cube.
		
		Face is visible if vertices are ordered clockwise.
	*/
    
#ifdef CUBE
	Mesh *mesh = new Mesh(8, 12);
	mesh->vertices[0] = Vector3(-1, 1, 1);
	mesh->vertices[1] = Vector3(1, 1, 1);
	mesh->vertices[2] = Vector3(1, -1, 1);
	mesh->vertices[3] = Vector3(-1, -1, 1);
	mesh->vertices[4] = Vector3(-1, 1, -1);
	mesh->vertices[5] = Vector3(1, 1, -1);
	mesh->vertices[6] = Vector3(1, -1, -1);
	mesh->vertices[7] = Vector3(-1, -1, -1);

	mesh->faces[0] = Face(3, 0, 1);
	mesh->faces[1] = Face(1, 2, 3);
	mesh->faces[2] = Face(7, 4, 0);
	mesh->faces[3] = Face(0, 3, 7);
	mesh->faces[4] = Face(5, 4, 7);
	mesh->faces[5] = Face(7, 6, 5);

	mesh->faces[6] = Face(1, 5, 6);
	mesh->faces[7] = Face(6, 2, 1);
	mesh->faces[8] = Face(4, 5, 1);
	mesh->faces[9] = Face(1, 0, 4);
	mesh->faces[10] = Face(2, 6, 7);
	mesh->faces[11] = Face(7, 3, 2);
#endif
	
	
	// Icosahedron
	// (Don't forget to correct Device::render
	//  and adjust camera position!)
#ifdef ICOSAHEDRON
	cameraLocation = 10;
	
	Mesh *mesh = new Mesh(12, 20);
	float t = (1.0 + sqrt(5.0)) / 2.0;
	
	mesh->vertices[0] = Vector3( 0,  t,  1);
	mesh->vertices[1] = Vector3( 0,  t, -1);
	mesh->vertices[2] = Vector3( 0, -t,  1);
	mesh->vertices[3] = Vector3( 0, -t, -1);
	
	mesh->vertices[4] = Vector3( t, -1,  0);
	mesh->vertices[5] = Vector3( t,  1,  0);
	mesh->vertices[6] = Vector3(-t, -1,  0);
	mesh->vertices[7] = Vector3(-t,  1,  0);

	mesh->vertices[8] =  Vector3(-1,  0, -t);
	mesh->vertices[9] =  Vector3( 1,  0, -t);
	mesh->vertices[10] = Vector3(-1,  0,  t);
	mesh->vertices[11] = Vector3( 1,  0,  t);

	// create 20 triangles of the icosahedron
	mesh->faces[0] = Face(0, 1, 5);
	mesh->faces[1] = Face(5, 4, 11);
	mesh->faces[2] = Face(11, 10, 0);
	mesh->faces[3] = Face(0, 5, 11);
	mesh->faces[4] = Face(1, 9, 5);
	mesh->faces[5] = Face(5, 9, 4);
	mesh->faces[6] = Face(11, 4, 2);
	mesh->faces[7] = Face(11, 2, 10);
	mesh->faces[8] = Face(10, 7, 0);
	mesh->faces[9] = Face(7, 1, 0);
	mesh->faces[10] = Face(8, 6, 3);
	mesh->faces[11] = Face(8, 7, 6);
	mesh->faces[12] = Face(6, 2, 3);
	mesh->faces[13] = Face(3, 9, 8);
	mesh->faces[14] = Face(8, 1, 7);
	mesh->faces[15] = Face(6, 7, 10);
	mesh->faces[16] = Face(2, 6, 10);
	mesh->faces[17] = Face(4, 3, 2);
	mesh->faces[18] = Face(9, 3, 4);
	mesh->faces[19] = Face(9, 1, 8);
#endif

	// Simple space ship
#ifdef SPACESHIP
	Mesh *mesh = new Mesh(4,4);
	mesh->vertices[0] = Vector3(0,-0.5,1);
	mesh->vertices[1] = Vector3(0.5,-0.5,-1);
	mesh->vertices[2] = Vector3(-0.5,-0.5,-1);
	mesh->vertices[3] = Vector3(0, 0.5,-1);
	
	mesh->faces[0] = Face(1,3,2);
	mesh->faces[1] = Face(0,3,1);
	mesh->faces[2] = Face(0,2,3);
	mesh->faces[3] = Face(0,1,2);
#endif
	
	meshes[0] = mesh;
	
	camera = new Camera();
	camera->position = Vector3(0, 0, cameraLocation);
	camera->target = Vector3::zero();
}

void loop()
{
	device->clear();

	Mesh *mesh = meshes[0];
	
	mesh->rotation.x += 0.01;
	mesh->rotation.y += 0.01;

	device->render(camera, meshes, 1);

	device->present();
}

