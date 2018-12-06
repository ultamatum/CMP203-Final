#pragma once
#include "Shape.h"
#include "Model.h"
#include "Vector3.h"
#include "SOIL.h"

class GameObject
{
	public:
		GameObject();
		~GameObject();

		void Update();

		Vector3 position = { 0, 0, 0 };	//Position Vector
		Vector3 velocity = { 0, 0, 0 };	//Velocity Vector
		Vector3 rotation = { 0, 0, 0 }; //Rotation Vector
		GLuint texture;

	private:

};

