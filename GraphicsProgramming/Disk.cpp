#include "Disk.h"

Disk::Disk() 
{
	isQuads = false;
}

Disk::~Disk() {}

void Disk::Init(int resolution, float radius)
{
	double interval = ((2 * 3.141592) / resolution);

	for (int i = 0; i < resolution; i++)
	{
		#pragma region Centre Vertex
		vertices.push_back(0);	//x
		vertices.push_back(0);	//y
		vertices.push_back(0);	//z

		texCoords.push_back(0.5);	//u
		texCoords.push_back(0.5);	//v

		normals.push_back(0);	//x
		normals.push_back(0);	//y
		normals.push_back(1);	//z
#pragma endregion

	#pragma region Outside vertex
		vertices.push_back(radius * cos(interval * i));	//x
		vertices.push_back(radius * sin(interval * i));	//y
		vertices.push_back(0);	//z

		texCoords.push_back((cos(interval * i) / (radius * 2)) + 0.5);	//u
		texCoords.push_back((sin(interval * i) / (radius * 2)) + 0.5);	//v

		normals.push_back(0);	//x
		normals.push_back(0);	//y
		normals.push_back(1);	//z
#pragma endregion

		#pragma region Outside Vertex + 1
		vertices.push_back(radius * cos(interval * (i + 1)));	//x
		vertices.push_back(radius * sin(interval * (i + 1)));	//y
		vertices.push_back(0);

		texCoords.push_back((cos(interval * (i + 1)) / (radius * 2)) + 0.5);	//u
		texCoords.push_back((sin(interval * (i + 1)) / (radius * 2)) + 0.5);	//v

		normals.push_back(0);	//x
		normals.push_back(0);	//y
		normals.push_back(1);	//z
#pragma endregion
	}
}
