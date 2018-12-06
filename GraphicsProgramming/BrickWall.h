#pragma once
#include "GameObject.h"
#include "Cuboid.h"

class BrickWall : public GameObject
{
	public:
		BrickWall();
		~BrickWall();

		void Render();

	private:
		Cuboid model;
};

