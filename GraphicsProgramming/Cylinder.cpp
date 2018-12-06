#include "Cylinder.h"

Cylinder::Cylinder()
{
	isQuads = true;
}

Cylinder::~Cylinder() {}

void Cylinder::Init(int lat, int lon, float h, float r)
{
	longitude = lon;
	latitude = lat;
	height = h;
	radius = r;

	vertices.clear();
	texCoords.clear();
	normals.clear();

	float latInt = h / lat;
	float latTexInc = 1.0 / lat;
	float lonTexInc = 1.0 / lon;
	float longDeltaInt = 3.141592 / lon;
	float latThetaInt = -((2 * 3.141592) / lat);

	for (int y = 0; y < lat; y++)
	{
		for (int x = 0; x < lon; x++)
		{
			//Adds the bottom left vertex to the vector
			#pragma region Bottom Left Vertex
			vertices.push_back(r * cos(latThetaInt * y));	//x
			vertices.push_back(r * (latInt * x));	//y
			vertices.push_back(r * sin(latThetaInt * y));	//z

			texCoords.push_back(latTexInc * y);	//u
			texCoords.push_back(lonTexInc * x);	//v

			normals.push_back((r * cos(latThetaInt * y)) / r);	//x
			normals.push_back((r * (latInt * x)) / r);	//y
			normals.push_back((r * sin(latThetaInt * y)) / r);	//z
#pragma endregion

			#pragma region Bottom Right Vertex
			vertices.push_back(r * cos(latThetaInt * y));	//x
			vertices.push_back(r * (latInt * (x + 1)));	//y
			vertices.push_back(r * sin(latThetaInt * y));	//z

			texCoords.push_back(latTexInc * y);		//u
			texCoords.push_back(lonTexInc * (x + 1));	//v
			
			normals.push_back((r * cos(latThetaInt * y)) / r);	//x
			normals.push_back((r * (latInt * (x + 1))) / r);	//y
			normals.push_back((r * sin(latThetaInt * y)) / r);	//z
#pragma endregion

			#pragma region Top Right Vertex
			vertices.push_back(r * cos(latThetaInt * (y + 1)));	//x
			vertices.push_back(r * (latInt * (x + 1)));	//y
			vertices.push_back(r * sin(latThetaInt * (y + 1)));	//z

			texCoords.push_back(latTexInc * (y + 1));	//u
			texCoords.push_back(lonTexInc * (x + 1));	//v

			normals.push_back((r * cos(latThetaInt * (y + 1))) / r);	//x
			normals.push_back((r * (latInt * (x + 1))) / r);	//y
			normals.push_back((r * sin(latThetaInt * (y + 1))) / r);	//z
#pragma endregion

			#pragma region Top Left Vertex
			vertices.push_back(r * cos(latThetaInt * (y + 1)));	//x
			vertices.push_back(r * (latInt * x));	//y
			vertices.push_back(r * sin(latThetaInt * (y + 1)));	//z

			texCoords.push_back(latTexInc * (y + 1));	//u
			texCoords.push_back(lonTexInc * x);	//v

			normals.push_back((r * cos(latThetaInt * (y + 1))) / r);	//x
			normals.push_back((r * (latInt * x)) / r);	//y
			normals.push_back((r * sin(latThetaInt * (y + 1))) / r);	//z
#pragma endregion
		}
	}
}
