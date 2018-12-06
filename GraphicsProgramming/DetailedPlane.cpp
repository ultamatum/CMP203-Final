#include "DetailedPlane.h"

DetailedPlane::DetailedPlane() 
{
	isQuads = true;
}

DetailedPlane::~DetailedPlane() {}

void DetailedPlane::Init(int res, float w, float d)
{
	resolution = res;
	width = w;
	depth = d;
	
	vertices.clear();
	texCoords.clear();
	normals.clear();

	for (int z = 0; z < d * res; z++)
	{
		for (int x = 0; x < w * res; x++)
		{
			#pragma region Top Left Vertex
			vertices.push_back((x / res) - (w / 2));		//x
			vertices.push_back(0);							//y
			vertices.push_back((z / res) - (d / 2));		//z

			texCoords.push_back(x / res);
			texCoords.push_back(z / res);

			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
			#pragma endregion

			#pragma region Bottom Left Vertex
			vertices.push_back((x / res) - (w / 2));		//x
			vertices.push_back(0);							//y
			vertices.push_back(((z + 1) / res) - (d / 2));	//z

			texCoords.push_back(x / res);	//u
			texCoords.push_back((z + 1) / res);	//v

			normals.push_back(0);		//x
			normals.push_back(1);		//y
			normals.push_back(0);		//z
			#pragma endregion

			#pragma region Bottom Right Vertex
			vertices.push_back(((x + 1) / res) - (w / 2));	//x
			vertices.push_back(0);							//y
			vertices.push_back(((z + 1) / res) - (d / 2));	//z

			texCoords.push_back((x + 1) / res);	//u
			texCoords.push_back((z + 1) / res);	//v

			normals.push_back(0);		//x
			normals.push_back(1);		//y
			normals.push_back(0);		//z
			#pragma endregion

			#pragma region Top Left Vertex
			vertices.push_back(((x + 1) / res) - (w / 2));	//x
			vertices.push_back(0);							//y
			vertices.push_back((z / res) - (d / 2));		//z

			texCoords.push_back((x + 1) / res);	//u
			texCoords.push_back(z / res);	//v

			normals.push_back(0);		//x
			normals.push_back(1);		//y
			normals.push_back(0);		//z
			#pragma endregion
		}
	}
}
