#include "Cuboid.h"

Cuboid::Cuboid()
{
	isQuads = true;
}

Cuboid::~Cuboid() {}

//Initialises a simple cuboid using 4 variables:
//The length of the cuboid
//The height of the cuboid
//The depth of the cuboid
//The texture scale (how many times the texture repeats)
void Cuboid::Init(float l, float h, float d, float texScale)
{
	length = l;
	height = h;
	depth = d;

	vertices.clear();
	texCoords.clear();
	normals.clear();

	#pragma region Front
		#pragma region Bottom Left
			vertices.push_back(-0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			#pragma endregion

		#pragma region Bottom Right
			vertices.push_back(0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			#pragma endregion

		#pragma region Top Right
			vertices.push_back(0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			#pragma endregion

		#pragma region Top Left
			vertices.push_back(-0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(1);
			#pragma endregion
		#pragma endregion

	#pragma region Back
		#pragma region Bottom Left
			vertices.push_back(0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(-1);
		#pragma endregion

		#pragma region Bottom Right
			vertices.push_back(-0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(-1);
		#pragma endregion

		#pragma region Top Right
			vertices.push_back(-0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(-1);
		#pragma endregion

		#pragma region Top Left
			vertices.push_back(0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(0);
			normals.push_back(0);
			normals.push_back(-1);
		#pragma endregion
	#pragma endregion

	#pragma region Left
		#pragma region Bottom Left
			vertices.push_back(-0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(-1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion

		#pragma region Bottom Right
			vertices.push_back(-0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(-1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion

		#pragma region Top Right
			vertices.push_back(-0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(-1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion

		#pragma region Top Left
			vertices.push_back(-0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(-1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion
	#pragma endregion

	#pragma region Right
		#pragma region Bottom Left
			vertices.push_back(0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion

		#pragma region Bottom Right
			vertices.push_back(0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion

		#pragma region Top Right
			vertices.push_back(0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion

		#pragma region Top Left
			vertices.push_back(0.5 * l);
			vertices.push_back(0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(1);
			normals.push_back(0);
			normals.push_back(0);
		#pragma endregion
	#pragma endregion

	#pragma region Top
	#pragma region Bottom Left
		vertices.push_back(-0.5 * l);
		vertices.push_back(0.5 * h);
		vertices.push_back(0.5 * d);

		texCoords.push_back(0 * texScale);
		texCoords.push_back(1 * texScale);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
		#pragma endregion

	#pragma region Bottom Right
		vertices.push_back(0.5 * l);
		vertices.push_back(0.5 * h);
		vertices.push_back(0.5 * d);

		texCoords.push_back(1 * texScale);
		texCoords.push_back(1 * texScale);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
		#pragma endregion

	#pragma region Top Right
		vertices.push_back(0.5 * l);
		vertices.push_back(0.5 * h);
		vertices.push_back(-0.5 * d);

		texCoords.push_back(1 * texScale);
		texCoords.push_back(0 * texScale);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
		#pragma endregion

	#pragma region Top Left
		vertices.push_back(-0.5 * l);
		vertices.push_back(0.5 * h);
		vertices.push_back(-0.5 * d);

		texCoords.push_back(0 * texScale);
		texCoords.push_back(0 * texScale);

		normals.push_back(0);
		normals.push_back(1);
		normals.push_back(0);
		#pragma endregion
#pragma endregion

	#pragma region Bottom
		#pragma region Bottom Left
			vertices.push_back(-0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(0);
			normals.push_back(-1);
			normals.push_back(0);
#pragma endregion

		#pragma region Bottom Right
			vertices.push_back(0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(1 * texScale);

			normals.push_back(0);
			normals.push_back(-1);
			normals.push_back(0);
#pragma endregion

		#pragma region Top Right
			vertices.push_back(0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(1 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(0);
			normals.push_back(-1);
			normals.push_back(0);
#pragma endregion

		#pragma region Top Left
			vertices.push_back(-0.5 * l);
			vertices.push_back(-0.5 * h);
			vertices.push_back(-0.5 * d);

			texCoords.push_back(0 * texScale);
			texCoords.push_back(0 * texScale);

			normals.push_back(0);
			normals.push_back(-1);
			normals.push_back(0);
#pragma endregion
#pragma endregion
}
