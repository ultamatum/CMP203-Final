#include "Sphere.h"

Sphere::Sphere()
{
	isQuads = true;
}

Sphere::~Sphere() {}

void Sphere::Init(int lat, int lon, float r)
{
	longitude = lon;
	latitude = lat;
	radius = r;

	vertices.clear();
	texCoords.clear();
	normals.clear();

	float latTexInc = 1.0 / lat;
	float lonTexInc = 1.0 / lon;
	float longDelta = 3.141592 / lon;
	float latTheta = -((2 * 3.141592) / lat);

	for (int y = 0; y < lat; y++)
	{
		for (int x = 0; x < lon; x++)
		{
			//Deals with the top left vertex of the quad
			#pragma region Top Left
			vertices.push_back((r * cos(latTheta * y)) * sin(longDelta * x));		//x
			vertices.push_back(r * cos(longDelta * x));								//y
			vertices.push_back((r * sin(latTheta * y)) * sin(longDelta * x));		//z

			texCoords.push_back(latTexInc * y);										//u
			texCoords.push_back(lonTexInc * x);										//v

			normals.push_back(((r * cos(latTheta * y)) * sin(longDelta * x)) / r);	//x
			normals.push_back((r * cos(longDelta * x)) / r);	//y
			normals.push_back(((r * sin(latTheta * y)) * sin(longDelta * x)) / r);	//z
#pragma endregion

			//Deals with the bottom left vertex of the quad
			#pragma region Bottom Left
			vertices.push_back((r * cos(latTheta * y)) * sin(longDelta * (x + 1)));	//x
			vertices.push_back(r * cos(longDelta * (x + 1)));	//y
			vertices.push_back((r * sin(latTheta * y)) * sin(longDelta * (x + 1)));	//z

			texCoords.push_back(latTexInc * y);	//u
			texCoords.push_back(lonTexInc * (x + 1));	//v

			normals.push_back(((r * cos(latTheta * y)) * sin(longDelta * (x + 1))) / r);	//x
			normals.push_back((r * cos(longDelta * (x + 1))) / r);	//y
			normals.push_back(((r * sin(latTheta * y)) * sin(longDelta * (x + 1))) / r);	//y
#pragma endregion

			//Deals with the bottom right vertex of the quad
			#pragma region Bottom Right 
			vertices.push_back((r * cos(latTheta * (y + 1))) * sin(longDelta * (x + 1)));	//x
			vertices.push_back(r * cos(longDelta * (x + 1)));	//y
			vertices.push_back((r * sin(latTheta * (y + 1))) * sin(longDelta * (x + 1)));	//z

			texCoords.push_back(latTexInc * (y + 1));	//u
			texCoords.push_back(lonTexInc * (x + 1));

			normals.push_back(((r * cos(latTheta * (y + 1))) * sin(longDelta * (x + 1))) / r);	//x
			normals.push_back((r * cos(longDelta * (x + 1))) / r);	//y
			normals.push_back(((r * sin(latTheta * (y + 1))) * sin(longDelta * (x + 1))) / r);	//z

#pragma endregion

			//Deals with the top right vertex of the quad
			#pragma region Top Right
			vertices.push_back((r * cos(latTheta * (y + 1))) * sin(longDelta * x));	//x
			vertices.push_back(r * cos(longDelta * x));								//y
			vertices.push_back((r * sin(latTheta * (y + 1))) * sin(longDelta * x));	//z

			texCoords.push_back(latTexInc * (y + 1));	//u
			texCoords.push_back(lonTexInc * x);			//v

			normals.push_back(((r * cos(latTheta * (y + 1))) * sin(longDelta * x)) / r);	//x
			normals.push_back((r * cos(longDelta * x)) / r);	//y
			normals.push_back(((r * sin(latTheta * (y + 1))) * sin(longDelta * x)) / r);	//z
#pragma endregion
		}
	}
}
